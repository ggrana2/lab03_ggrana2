#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return this->numStudents;
}

Student Roster::getStudentAt(int index) const { 
  return *(this->students[index]);
}

std::string Roster::toString() const {
  std::string result = "{\n";

  for(int i = 0; i < numStudents-1; i++){
  	result += this->students[i]->toString() + ",";
	result += "\n";
  };

  result += this->students[numStudents-1]->toString();	
  result += "\n" ;
  result += "}\n";
  return result;

}

void Roster::sortByPerm() {

	for(int i = numStudents-1; i > 0; i--){
		//int largest = this->students[indexOfMaxPermAmongFirstKStudents(i);
		sortByPermHelper(i);

	}
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
	if(numStudents == 0){
		return -1;
	}
	int max = (this->students[0])->getPerm();
	int maxIndex = 0;

	if(k > this->numStudents){
		k = this->numStudents-1;
	}

	for(int i = 1; i <= k-1; i++){
		if((this->students[i])->getPerm() > max){
			max = (this->students[i])->getPerm();
			maxIndex = i;
		}
	}
	

	return maxIndex; 
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]

  int im = indexOfMaxPermAmongFirstKStudents(k);
  Student* temp1 = this->students[im];
  Student* temp2 = this->students[k-1];
  this->students[k-1] = temp1;
  this->students[im] = temp2;

  // now swap the pointers between index im and index k-1

  // THIS IS STILL A STUB !!!
  
}
