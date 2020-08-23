#include <iostream>
#include <fstream>
#include "notebook.hpp"
#include <string>
#include <vector>
//This file creates a note maker

int main()
{
    bool exit = false;
    std::cout << "Welcome to TuffyNotes!\n";
    Notebook notes(100);
    while (exit == false)
    {
        std::string choice = "";
        while (!(choice == "c" || choice == "e" || choice == "l" || choice == "v" || choice == "s" || choice == "o"))
        {
            choice = add_question();
            if (choice == "c")
            {
                if (notes.get_size() < 100)
                {
                    Note new_note = create_note();
                    notes.add(new_note);
                    std::cout << "\nNote added!\n\n";
                }
                else
                {
                    std::cout << "Maximum number of notes reached (100)." << std::endl;
                }

            }
            else if (choice == "e")
            {
                exit = true;
            }
            else if (choice == "v")
            {
                notes.view_note();
            }
            else if (choice == "l")
            {
                notes.list_notes();
            }
            else if (choice == "s")
            {
                std::string file_name;

                std::cout << "\n\nPlease enter the filename: \n";
                std::getline(std::cin, file_name);

                notes.save_notes(file_name);
            }
            else if (choice == "o")
            {
                std::string file_name1;

                std::cout << "\nPlease enter the filename: ";
                std::getline(std::cin, file_name1);
                notes.load_notes(file_name1);
            }
            else
            {
                std::cout << "\nInvalid choice. Please try again.\n" << std::endl;
            }
        }
    }
    std::cout << "\nThank you for using TuffyNotes!" << std::endl;
    return 0;
}
