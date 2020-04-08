#include <iostream>
using namespace std;

class PrintedMaterial {
public:
  PrintedMaterial( unsigned numPages )
    : numOfPages(numPages)
  {}

  //               LOOK AT THE = 0
  virtual void displayNumPages() const = 0;
private:
  unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
}

class Magazine : public PrintedMaterial {
public:
  Magazine( unsigned numPages )
    : PrintedMaterial(numPages)
  {}
};

class Book : public PrintedMaterial {
public:
  Book( unsigned numPages)
    : PrintedMaterial(numPages)
  {}
};

class TextBook : public Book {
public:
  TextBook( unsigned numPages, unsigned numIndxPgs  )
    : Book(numPages),
      numOfIndexPages(numIndxPgs)
  {}
  void displayNumPages() const {
    cout << "Pages: ";
    PrintedMaterial::displayNumPages();
    cout << "Index pages: ";
    cout << numOfIndexPages << endl; 
  }
private:
  unsigned numOfIndexPages;
};

class Novel : public Book {
public:
  Novel( unsigned numPages )
    : Book(numPages)
  {}
};


// note that reference to PrintedMaterial is the parameter type
// now we can use the dot member operator
// if use the -> operator, thats not going to work (try it!)
void displayNumberOfPages( const PrintedMaterial& anyPM ) {
  anyPM.displayNumPages();
}


// tester/modeler code
int main() {
  TextBook t(5430, 23);
  Novel n(213);
  Magazine m(6);

  t.displayNumPages();
  n.displayNumPages();
  m.displayNumPages();

  cout << "\nA PrintedMaterial material object!\n";
  PrintedMaterial pm(2345);
  pm.displayNumPages();

  pm = t; // like putting a t into a vector of PrintedMaterials
  pm.displayNumPages();

  cout << "\nUsing PrintedMaterial* to \"store\" a TextBook object\n";
  cout << "Now with the virtual mechanism involved\n";
  // should work now that the virtual mechanism is being invoked
  PrintedMaterial* pmPtr;
  pmPtr = &t; // like putting t into a vector but
  // we are actually putting the address of t
  // into a vector pointers of pointers to
  // PrintedMaterials. We'll "say" we are putting
  pmPtr->displayNumPages();

  // print some stuff by calling a generic function
  cout << "\nUse a generic functino for printing\n";
  displayNumberOfPages(m);
  displayNumberOfPages(n);
  displayNumberOfPages(t);
}

