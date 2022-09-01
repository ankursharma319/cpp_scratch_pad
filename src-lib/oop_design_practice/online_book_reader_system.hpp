#ifndef ONLINE_BOOK_READER_SYSTEM_HPP
#define ONLINE_BOOK_READER_SYSTEM_HPP

#include <cstddef>
#include <string>
#include <optional>
#include <utility>
#include <unordered_map>
#include <vector>

// This is a proposal for question 7.5 in CTCI

// Assumptions
// going to implement the backend which might be queried via different clients/apis
// not going to concern with database & persistent for now, just a demoable thing
// no login/registration - open to all - store preferences in cookies or tmp

// objects
/*
- Book
- BookPage
- Author
- Genre (enum)
- Library

// relations
- Book has many BookPages - one to many
- Author and books <-> many to many
- Library has books 

// algorithms (requirements)
- search books by title name, author, genre
- search content of all books
- retrieve page content quickly

Future
- users(customers)
- physical bookmarks
- book recommendations based on activity
*/

namespace book_reader_system {

class Author {
public:
    std::string first_name() const;
    std::string last_name() const; 
    std::string bio() const;

    std::vector<std::size_t> book_ids() const;
};

enum class Genre {
    Biography, Fiction, Horror, Novel, Science, Technology,
};

enum class FontTypeFace {
    Ariel, Calibri, TimesNewRoman
};

class AppearancePreference {
public:
    enum class Justification {
        Left, Center, Right
    };
    std::size_t font_size();
    std::uint32_t font_color();
    std::uint32_t background_color();
    FontTypeFace font_type();
    Justification text_justification();
    std::size_t number_of_columns();
};

struct Image {
    std::string url;
    std::string caption;
    std::pair<float, float> origin;
    std::pair<float, float> size;
};

class BookPage {
public:
    std::size_t page_number() const;
    std::string content() const;
    std::vector<Image> images() const;
    AppearancePreference preference() const;
    std::size_t book_id() const;
    std::vector<float> document_vector() const;
};

class Book {
public:
    Book(std::istream is); // parse from xml/json/pdf/other ebook formats
    std::size_t id() const;
    std::optional<std::string> isdn() const;
    std::string title() const;
    std::vector<Author> authors() const;
    std::vector<BookPage> pages() const;
    std::vector<Genre> genres() const;
};

class Library {
public:
    Book get_book(std::size_t id);
    bool add_book(Book book);
    bool remove_book(std::size_t book_id);
    std::vector<Book> all_books();
    std::vector<Book> find_books_by_title(std::string const& title);
    std::vector<Book> find_books_by_author(Author const& author);
    std::vector<Book> find_books_by_genre(Genre genre);
    std::vector<BookPage> find_pages_by_content(std::string const& search);

private:
    std::unordered_map<std::size_t, Book> m_books {};
    // Trie m_trie_titles;
};

}

#endif
