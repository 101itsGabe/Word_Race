#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <type_traits>
#include <stdio.h>
#include <string.h>
#include <unordered_map>
#include <ctime>


using namespace std;


//Sort function takes in whichever map and sorts them accordingly
template <typename T, typename V>
void sort(unordered_map<T,V>& m) {
  int size = m.size();
  
  //If size is greater than 10 set to 10
  if (size > 10)
    size = 10;

  cout << "Total " << m.size() << " different ";
  if(is_same<T, char>::value) 
    cout << " character";
  else {
    auto titr = m.begin();
    string temp = "";
    temp += titr->first;
    if(isdigit(temp[0]))
      cout << " integers";
    else
      cout << " words";
  }
  
  cout << ", " << size << " most used:" << endl;



  for(int i = 0; i < size; i++) {
   auto fitr = m.begin();		//first iterator 
   
  //Loop running through map if the value of the loop iterator is greater than the first
  //iteraotr then replace as greatest itr 
   for(auto itr = m.begin(); itr != m.end(); itr++)  {
      if(fitr->second < itr->second)	
         fitr = itr;
      
      else if(fitr->second == itr->second){
	//if type is a char check against itr ascii value
        if(is_same<T, char>::value) { 
          string temp = "";
          string temp2 = "";
          temp += fitr->first;
          temp2 += itr->first;
           
          if(int(temp[0]) > int(temp2[0]))
            fitr = itr;
        }

 	//itr will always be the word before becasue they are entered
	//from the front
       else {
          fitr = itr;
       }

      }
      
   }   
   
   //checks to see if type T is char type for '\n' and '\t'
   string check = "";
   check += fitr->first;
   if(check[0] == '\n')
     cout << "No. " << i << setw(12) << "Phrase: \"" << "\\n" << "\"" << right << setw(22) << "Amount: " << fitr->second <<  endl;
   else if(check[0] == '\t')
     cout << "No. " << i << setw(12) << "Phrase: \"" << "\\t" << "\"" << right << setw(22) << "Amount: " << fitr->second <<  endl;
   else   
     cout << "No. " << i << setw(12) << "Phrase: \"" << fitr->first << "\"" << right << setw(22) << "Amount: " << fitr->second <<  endl; 

   //remove from map so not greatest anymore
   m.erase(fitr);
  }
  
}



int main(){

 string curPhrase;
 char inChar,inPeek;
 unordered_map <string,int> wordMap, intMap;
 unordered_map <char,int> letterMap;
 clock_t start, stop;


    start = clock();
    while(cin.get(inChar)) {

     if(isalpha(inChar))
       curPhrase += tolower(inChar);

     else if(isdigit(inChar))
      curPhrase += inChar;


    //pair with char read and bool to check if inside map already
    pair<unordered_map<char, int>::iterator, bool> inCheck;
    inCheck = letterMap.insert(pair<char, int>(inChar, 1));   
   
    if(inCheck.second == false)
     inCheck.first->second = inCheck.first->second + 1;  

     inPeek = cin.peek();
 
    //if the first char of curPhrase and the current inChar is Char or vice versa
    if(isdigit(inChar) && isalpha(inPeek) || isalpha(inChar) && isdigit(inPeek) || inPeek == EOF || !isdigit(inPeek) && !isalpha(inPeek)) {
      pair<unordered_map<string, int>::iterator, bool> ret;

      if(isdigit(curPhrase[0]))
       ret = intMap.emplace(pair<string, int>(curPhrase, 1));
      else if(curPhrase.find_first_not_of(' ') != std::string::npos)
       ret = wordMap.emplace(pair<string, int>(curPhrase, 1));
      else {
       curPhrase.clear();
       continue;
     }

      if(ret.second == false)
       ret.first->second = ret.first->second + 1;

      curPhrase.clear();
    }	//if end
 
 }
 


 if(!letterMap.empty()) 
   sort<char,int>(letterMap);
 cout << "\n";

 if(!wordMap.empty())
  sort<string,int>(wordMap);
 cout << "\n";

 if(!intMap.empty()) 
   sort<string,int>(intMap);
 cout <<"\n";

  stop = clock();
  cout << "Total Time: " << (stop - start)/(double)CLOCKS_PER_SEC << "s" << endl; 

return 0;
}
