#include "notebook.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
Note::Note()
{
    title_ = "Untitled";
    body_ = "";
}
Note::Note(const std::string &title, const std::string &body)
{
    title_ = title;
    body_ = body;
}
void Note::set_note_title(std::string title)
{
    title_ = title;
}
void Note::set_note_body(std::string body)
{
    body_ = body;
}

std::string Note::get_title_()
{
    return title_;
}

std::string Note::get_body_()
{
    return body_;
}

Note create_note()
{
    Note new_note;
    std::string title, body;

    std::cout << "\nPlease enter the note's title: ";
    std::getline(std::cin, title);
    std::cout << "Please enter the note: ";
    std::getline(std::cin, body);

    new_note.set_note_title(title);
    new_note.set_note_body(body);

    return new_note;
}

std::string add_question()
{
    std::string choice;
    std::cout << "[C] Create a note\n[L] List notes\n[V] View notes\n[S] Save notes\n[O] Open notes\n[E] Exit\nChoice:";
    std::getline(std::cin,choice);
    return choice;
}

Notebook::Notebook()
{
    capacity_ = 100;
    size_ = 0;
    notes_ = new Note[100];
}

Notebook::Notebook(int capacity)
{
    capacity_ = capacity;
    size_ = 0;
    notes_ = new Note[capacity];
}

Notebook::~Notebook()
{
    delete[] notes_;
    notes_ = nullptr;
}

int Notebook::get_capacity()
{
    return capacity_;
}

int Notebook::get_size()
{
    return size_;
}

void Notebook::add(Note &new_note)
{
    *(notes_ + size_) = new_note;
    size_ += 1;
}

Note Notebook::get(int index) const
{
    return *(notes_ + (index - 1));
}

void Notebook::list_notes() const
{
    if (size_ == 0)
    {
        std::cout << "\nNo notes have been added.\n" << std::endl;
    }
    else
    {
        std::cout << "\n";
        for (int i = 0; i < size_; i++)
        {
            std::cout << i+1 << ". " << (notes_ + i)->get_title_() << std::endl;
        }
        std::cout << "\n";
    }
}

void Notebook::view_note() const
{
    std::string index_choice = "";
    if (size_== 0)
    {
        std::cout << "\nNo notes have been added.\n";
    }
    else
    {
        list_notes();
        std::cout << "Please input the note index: ";
        std::cin >> index_choice;
        std::cin.ignore();

        bool valid_choice = false;
        while (valid_choice == false)
        {
            for (int i = 1; i <= size_; i++)
            {
                if (index_choice == std::to_string(i))
                {
                    valid_choice = true;
                }
            }
            if (valid_choice == false)
            {
                std::cout << "Invalid note index. Please enter a valid index.\n" << std::endl;
                std::cin >> index_choice;
                std::cin.ignore();
            }
        }
        std::cout << "\n[" << (notes_ + (stoi(index_choice) - 1))->get_title_() << "]\n";
        std::cout << (notes_ + (stoi(index_choice) - 1))->get_body_() << "\n" << std::endl;
    }
}

void Notebook::save_notes(const std::string &filename) const
{
    if (size_ == 0)
    {
        std::cout << "\nYou currently have no notes available to save.\n" << std::endl;
        return;
    }

    std::ofstream note_file(filename);
    if (note_file.is_open())
    {
        note_file << size_;
        for (int i = 0; i < size_; i++)
        {
            note_file << "\n[Note]\n";
            note_file << (notes_ + i)->get_title_() << "\n";
            note_file << (notes_ + i)->get_body_();
        }
        note_file.close();
        std::cout << "File saved successfully!\n" << std::endl;
    }
}

void Notebook::load_notes(const std::string &filename)
{
    Note loaded_note;
    std::ifstream load_list(filename);
    if (load_list.is_open())
    {
        std::string num_string;
        std::getline(load_list, num_string);
        size_ = stoi(num_string);

        std::cout << "File loaded successfully!\n" << std::endl;

        while (load_list.good())
        {
            for (int i = 0; i < (size_); i++)
            {
                load_list.ignore(100, '\n');

                std::string new_title, new_body;
                std::getline(load_list,new_title);
                std::getline(load_list,new_body);

                loaded_note.set_note_title(new_title);
                loaded_note.set_note_body(new_body);
                *(notes_ + i) = loaded_note;
            }
        }

        load_list.close();
    }
}
