
/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * conv3d.cpp source file with all declarations for Conv3D class
 *
 */


#include "../include/conv3d.hpp"


//------------------------------------------------------------------------------


/**
 * Default constructor for class 
 * Instantatiates a vector of vector of Kernels (square 3 dimensional tensors of given size)
 * with the LReLu activation function
 *
 * @param tensor_size square size of 3 dimensional filters
 * @param particles size of 4th dimension
 * @param size amount of filters (Kernels)
 * 
 */
Conv3D::Conv3D(unsigned tensor_size, 
               unsigned particles, 
               unsigned size)
    : kernels{size, std::vector<Kernel>(particles, Kernel(tensor_size))}
{
    activation_function = [](double input) -> double { return std::max(input, input*0.01); };
}


//------------------------------------------------------------------------------


/**
 * Instantatiates a vector of vector of Kernels (square 3 dimensional tensors of given size)
 * with a given activation function
 *
 * @param tensor_size square size of 3 dimensional filters
 * @param particles size of 4th dimension
 * @param size amount of filters (Kernels)
 * @param activation_function lambda defined somewhere else
 * 
 */
Conv3D::Conv3D(unsigned tensor_size,
               unsigned particles,
               unsigned size,
               FunctionPointer activation_function)
    : kernels{size, std::vector<Kernel>(particles, Kernel(tensor_size))},
      activation_function{activation_function}
{
    
}


//------------------------------------------------------------------------------


/**
 * This function simplifies the calculation process of the inner product of both
 * tensors (channel and filter) in order to avoid a 5 nested for loop in the 
 * feed forward function
 *
 * @param channel is a 3 dimensional square tensor
 * @param kernel also
 *
 * @return activated value to be directly saved on the resulting channel
 *
 */
double Conv3D::calculate_inner_product(bnu::tensor<double>& channel, 
                                       bnu::tensor<double>& kernel)
{
    if (channel.size(2)!=kernel.size(2) || channel.size(1)!=kernel.size(1) || channel.size(0)!=kernel.size(0))
        throw std::runtime_error("Unmatching sizes on kernel and channel part");

    double acc = 0.0;
    for (auto k = 0ul; k < channel.size (2); ++ k)
        for (auto j = 0ul; j < channel.size (1); ++ j)
            for (auto i = 0ul; i < channel.size (0); ++ i)
                acc += channel.at(i,j,k) * kernel.at(i,j,k);

    return activation_function(acc/ (channel.size(0)*channel.size(0)*channel.size(0)));
}


//------------------------------------------------------------------------------


/**
 * Helper function for conv3d feed forward
 * it creates a bigger sized tensor with additional layers of zeros
 * and contians the channel inside the padding
 * this is needed in order to deliver the same amount of dimensions
 * in the output
 *
 * @param tensor is the whole tensor to be padded
 * @param new_size is the sum of paddings around the tensor
 * @param padding and size of the zero layers
 *
 * @return tensor with surrounding zeros
 *
 */
bnu::tensor<double> Conv3D::pad_channel(bnu::tensor<double>& tensor, 
                                        unsigned new_size, 
                                        unsigned padding)
{
    bnu::tensor<double> result{new_size, new_size, new_size};
    for (auto i=0ul; i<result.size(0); ++i)
        for (auto j=0ul; j<result.size(1); ++j)
            for (auto k=0ul; k<result.size(2); ++k)
                result.at(i,j,k) = 0.0;

    for (auto i=0ul; i<tensor.size(0); ++i)
        for (auto j=0ul; j<tensor.size(1); ++j)
            for (auto k=0ul; k<tensor.size(2); ++k)
                result.at(i+padding,j+padding,k+padding) = tensor.at(i,j,k);

    return result;
}


//------------------------------------------------------------------------------


/**
 * Helper function for feedforward in conv3d
 * it extracts a tensor from the channel with a matching size
 * to be calculate with the filter or kernel
 *
 * @param channel is the reference to tensor where data will be extracted
 * @param i_momentum is the current x coordinate
 * @param i_azimuth is the current y coordinate
 * @param i_inclination is the current z coordinate
 * @param s_fil is the window size to extract
 *
 * @return a tensor with the right size for the filtering calculations
 *
 */
bnu::tensor<double> Conv3D::create_sub_channel(bnu::tensor<double>& channel,
                                               unsigned i_momentum,
                                               unsigned i_azimuth, 
                                               unsigned i_inclination,
                                               unsigned s_fil,
                                               unsigned padding)
{

    bnu::tensor<double> sub_channel{s_fil, s_fil, s_fil};

    for (unsigned i=i_momentum-padding; i<i_momentum+s_fil; ++i)
        for (unsigned j=i_azimuth-padding; j<i_azimuth+s_fil; ++j)
            for (unsigned k=i_inclination-padding; k<i_inclination+s_fil; ++k)
                sub_channel.at(i-i_momentum,j-i_azimuth,k-i_inclination) = 
                    channel.at(i_momentum, i_azimuth, i_inclination);

    return sub_channel;
}

//------------------------------------------------------------------------------


/**
 * Feed Forward for a convolutional layer 
 * Iterate over all filters in the kernels list
 * Append zeros to the missing vectors on all four dimensions (Padding in filtering)
 * Iterate then over all the 4 dimensions retaining each of the tensors
 * Iterate over the tensors and performe the inner product with a matching size 
 * of each of the tensors saving the result on a new Channel which gets appended to a vector
 *
 * @param channels is a list of square 3 dimensional tensors
 *
 * @return the resulting tensors for the next convolutional layer
 *
 */
std::vector<Channel> Conv3D::feed_forward(std::vector<Channel>& channels)
{
    std::vector<Channel> results(kernels.size(), Channel(kernels[0][0].tensor.size(2)));
    unsigned padding = kernels[0][0].tensor.size(0) / 2;   // amount of zeros to append for full tensor
    unsigned new_size = channels[0].tensor.size(0)+2*padding;
    unsigned s_fil = kernels[0][0].tensor.size(0);      // filter size
    
    for (unsigned i_filter=0; i_filter<kernels.size(); ++i_filter) {
        Channel result(channels[0].tensor.size(0));

        for (unsigned i_tensor=0; i_tensor<kernels[i_filter].size(); ++i_tensor) {
            bnu::tensor<double> padded_current = pad_channel(channels[i_tensor].tensor, 
                                                             new_size, 
                                                             padding);

            for (unsigned i_momentum=0+padding; 
                    i_momentum<padded_current.size(0)-padding; ++i_momentum) {
                for (unsigned i_azimuth=0+padding; 
                        i_azimuth<padded_current.size(1)-padding; ++i_azimuth) {
                    for (unsigned i_inclination=0+padding; 
                            i_inclination<padded_current.size(2)-padding; ++i_inclination) {
                        
                        bnu::tensor<double> sub_channel = 
                            create_sub_channel(channels[i_tensor].tensor, i_momentum, i_azimuth, 
                                               i_inclination, s_fil, padding);

                        double value = calculate_inner_product(sub_channel, 
                                                               kernels[i_filter][i_tensor].tensor);

                        result.tensor.at(i_momentum,i_azimuth,i_inclination) += value;
                    }
                }
            }
        }
        results.push_back(result);   	    
    }
    return results;
}




