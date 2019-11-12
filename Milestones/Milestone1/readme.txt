# PRG-Praktikum WS19/20

## Milestone 1


Members:
	Joao Pargana		6807391
	Hendrik Edelmann	5920004
	Kai Wo Yau		6555025
	

Usage:
	Inside the code folder is a Makefile. Type *make* to compile both the terminal
	programs *GameOfLife* as the script *visualencrypt* which will be saved in
	the bin folder.

	The GameOfLife program contains a menu once launched, which provides all
	operations required in the exercise sheet and the visualencrypt script
	needs to be called as mentioned in Aufgabe 2. f).

	The a) and b) parts of the first exercise can be found in the code/Aufgabe1ab folder
	and one needs to type *make* to compile this seperate program from the project.

	To run the GUI version of the program navigate to the gui folder, type *qmake*
	to create a MakeFile followed by *make* and execute the gui binary.


Working hours:
	Each member focused on one of the exercises.
	Joao Pargana on Aufgabe 1 and programmed the matrix, cellular_automaton and
	game_of_life both header and source files.
	Hendrik Edelmann on Aufgabe 2 and programmed the vis_crypt header and source file.
	Kai Wo Yau on Aufgabe 3 and created all of the Qt code.

	We started a github REPO to coordinate the project between each other, each
	contains a list of everyone's commits and contribution to the project as well
	as the project management used with tickets, etc.
	The github REPO is private, but we could invite the Tutor to follow the teams
	work.

	The corresponding files contain a short comment section in the beginning
	referring to its authorship.

	The included header file *catch.hpp* is a third party library we used to perform
	unit tests. The command *make tester* will create the test script, which
	tests a small fraction of the classes created.


Bugs:
	The visualencrypt script still only provides the import and export features
	to a given file name, and even though the remaining are to be implemented
	the Qt GUI already contains the needed UI to communicate with the program.
