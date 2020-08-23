#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Note
{
private:
    std::string title_;
    std::string body_;
public:
    Note();
    Note(const std::string &title, const std::string &body);
    void set_note_title(std::string title);
    void set_note_body(std::string body);
    std::string get_title_();
    std::string get_body_();

};

class Notebook
{
private:
    int capacity_; //total number of notes that are stored in the notebook
    int size_; //current number of notes in the notebook
    Note *notes_ ; //pointer to an array of note objects
public:
    Notebook();
    Notebook(int capacity);
    ~Notebook();
    int get_capacity();
    int get_size();
    void add(Note &new_note);
    Note get(int index) const;
    void list_notes() const;
    void view_note() const;
    void save_notes(const std::string &filename) const;
    void load_notes(const std::string &filename);
};

Note create_note();
std::string add_question();
