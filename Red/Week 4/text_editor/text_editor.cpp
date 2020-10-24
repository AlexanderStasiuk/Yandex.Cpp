#include <string>
#include <list>
#include "test_runner.h"
using namespace std;

class Editor {
public:
    // Реализуйте конструктор по умолчанию и объявленные методы
    Editor(): 
        position_(text_.begin()),
        end_position_(text_.end()) {}

    void Left() {
        if (position_ != text_.begin()) {
            position_ --;
        }
    }
    void Right() {
        if (position_ != text_.end()) {
            position_ ++;
        }
    }
    void Insert(char token) {
        text_.insert(position_, token);
    }
    void Cut(size_t tokens = 1) {
        Copy(tokens);
        while (position_ != end_position_) {
            position_++;
            text_.erase(prev(position_));
        }
    }
    void Copy(size_t tokens = 1) {
        buffer_.clear();
        if (distance(position_, text_.end()) > tokens) {
            end_position_ = next(position_, tokens);
        } else {
            end_position_ = text_.end();
        }
        buffer_ = {position_, end_position_};
    }
    void Paste() {
        if (!buffer_.empty()) {
            text_.insert(position_, buffer_.begin(), buffer_.end());
        }
    }
    string GetText() const {
        return {text_.begin(), text_.end()};
    }
private:
    list<char> text_;
    list<char> buffer_;
    list<char>::iterator position_;
    list<char>::iterator end_position_;
};

void TypeText(Editor& editor, const string& text) {
  for(char c : text) {
    editor.Insert(c);
  }
}

void TestCopyPasteLastChars()
{
    Editor editor;
    TypeText(editor, "happy birthday");
    editor.Left();
    editor.Left();
    editor.Copy(5);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "happy birthdayay");
}


void TestEditing() {
  {
    Editor editor;

    const size_t text_len = 12;
    const size_t first_part_len = 7;
    TypeText(editor, "hello, world");

    for(size_t i = 0; i < text_len; ++i) {
      editor.Left();
    }
    
    editor.Cut(first_part_len);
    for(size_t i = 0; i < text_len - first_part_len; ++i) {
      editor.Right();
    }

    TypeText(editor, ", ");
    editor.Paste();
    editor.Left();
    editor.Left();
    editor.Cut(3);
    
    ASSERT_EQUAL(editor.GetText(), "world, hello");
  }
  {
    Editor editor;
    
    TypeText(editor, "misprnit");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    editor.Right();
    editor.Paste();
    
    ASSERT_EQUAL(editor.GetText(), "misprint");
  }
}

void TestReverse() {
  Editor editor;

  const string text = "esreveR";
  for(char c : text) {
    editor.Insert(c);
    editor.Left();
  }
  
  ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
  Editor editor;
  ASSERT_EQUAL(editor.GetText(), "");
  
  editor.Left();
  editor.Left();
  editor.Right();
  editor.Right();
  editor.Copy(0);
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
  Editor editor;

  editor.Paste();
  TypeText(editor, "example");
  editor.Left();
  editor.Left();
  editor.Paste();
  editor.Right();
  editor.Paste();
  editor.Copy(0);
  editor.Paste();
  editor.Left();
  editor.Cut(0);
  editor.Paste();
  
  ASSERT_EQUAL(editor.GetText(), "example");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestEditing);
  RUN_TEST(tr, TestReverse);
  RUN_TEST(tr, TestNoText);
  RUN_TEST(tr, TestEmptyBuffer);
  RUN_TEST(tr, TestCopyPasteLastChars);
  return 0;
}

// int main() {
//   Editor editor;
//   const string text = "hello, world";
//   for (char c : text) {
//     editor.Insert(c);
//   }
//   // Текущее состояние редактора: `hello, world|`
//   for (size_t i = 0; i < text.size(); ++i) {
//     editor.Left();
//   }
//   // Текущее состояние редактора: `|hello, world`
//   editor.Cut(7);
//   // Текущее состояние редактора: `|world`
//   // в буфере обмена находится текст `hello, `
//   for (size_t i = 0; i < 5; ++i) {
//     editor.Right();
//   }
//   // Текущее состояние редактора: `world|`
//   editor.Insert(',');
//   editor.Insert(' ');
//   // Текущее состояние редактора: `world, |`
//   editor.Paste();
//   // Текущее состояние редактора: `world, hello, |`
//   editor.Left();
//   editor.Left();
//   //Текущее состояние редактора: `world, hello|, `
//   editor.Cut(3); // Будут вырезаны 2 символа
//   // Текущее состояние редактора: `world, hello|`
//   cout << editor.GetText();
// }