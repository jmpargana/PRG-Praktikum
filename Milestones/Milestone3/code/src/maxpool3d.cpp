/**
 * PRG-Prakitkum WS19/20
 *
 * Author: Joao Pargana - 6807391
 * Gruppe: 3
 *
 * maxpool3d.cpp source file with all declarations for MaxPool3D class
 *
 */


#include "../include/maxpool3d.hpp"


//------------------------------------------------------------------------------


/**
 * Iterate over the pointer to the channel around the given coordinates
 * find the maximum value and return as a result
 *
 * @param channel is a pointer to the main tensor
 * @param i_momentum is the x1 coordinate
 * @param i_azimuth is the x2 coordinate
 * @param i_inclination is the x3 coordinate
 *
 * @return max value found
 *
 */
double MaxPool3D::find_max(bnu::tensor<double>* channel, 
                           unsigned i_momentum,
                           unsigned i_azimuth,
                           unsigned i_inclination)
{
    double max = channel->at(i_momentum, i_azimuth, i_inclination);

    for (unsigned i=i_momentum; i<i_momentum+2; ++i) {
        for (unsigned j=i_azimuth; j<i_azimuth+2; ++j) {
            for (unsigned k=i_inclination; k<i_inclination+2; ++k) {
                if (channel->at(i,j,k) > max) max = channel->at(i,j,k);
            }
        }
    }
    return max;
}



//------------------------------------------------------------------------------


/**
 * This function performs the feed forward in a max pool layer
 * it finds the maximum on each of 2x2x2 tensors and returns the result 
 * 
 * @param channels is a vector of tensors
 * @return list of smaller tensors
 *
 */
std::vector<Channel> MaxPool3D::feed_forward(std::vector<Channel>& channels)
{
    std::vector<Channel> results(channels.size(), Channel(channels[0].tensor.size(2) / 2));

    for (unsigned i_channel=0; i_channel<channels.size(); ++i_channel) {
        bnu::tensor<double>* curr = &channels[i_channel].tensor;
        
        for (unsigned i_momentum=0; i_momentum<curr->size(0)-2; i_momentum+=2) {
            for (unsigned i_azimuth=0; i_azimuth<curr->size(1)-2; i_azimuth+=2) {
                for (unsigned i_inclination=0; i_inclination<curr->size(2)-2; i_inclination+=2) {
                    results[i_channel].tensor.at(i_momentum/2, i_azimuth/2, i_inclination/2) = 
                        find_max(curr, i_momentum, i_azimuth, i_inclination);
                }
            }
        }
    }
    return results;
}
