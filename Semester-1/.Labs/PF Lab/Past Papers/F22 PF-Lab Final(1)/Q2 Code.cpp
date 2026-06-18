#include <iostream>
#include <cstring>
#include <string>
using namespace std;
int count_words(string arr[], int total_sentences);
void words_list(string sent[], int total_sentences, int word_count, string words[][6]);
void vocab(string words[][6], int word_count, string V[][6]);
int main()
{
  const int sentences = 4;
  string paragraph[sentences] = {"hello i am toqeer.", "how is the life?", "what is going in life?", "life is very short."};
  string words[18][6], V[18][6];
  int word_count; 
  cout<<"Counting the words in the given paragraph\n";
  word_count = count_words(paragraph, sentences);
  cout<<"The number of words in the given paragraph are: "<<word_count;
  cout<<"\nThe words of the paragraph seperated are:\n";
  words_list(paragraph, sentences, word_count, words);
  for(int i=0; i<word_count; ++i)
  {
    for(int j=0; j<6; ++j)
    {
      cout<<words[i][j];
    }
    if( i< (word_count-2) )
      cout<<",";
  }
  cout<<"\nThe vocabulary set of the given paragraph is\n";
  vocab(words, word_count, V);
  for(int i=0; i<word_count; ++i)
  {
    for(int j=0; j<6; ++j)
    {
      cout<<V[i][j];
    }
    if( i< (word_count-2) )
      cout<<",";
  }

  return 0;
}
int count_words(string arr[], int total_sentences)
{
  int counter = 1;
  char alpha = 0;
  for(int i=0; i<total_sentences; ++i)
  {
    for(int j=0; j<arr[i].length(); ++j)
    {
      alpha = arr[i][j];
      if( (alpha>64 && alpha<91) || (alpha>96 && alpha<123) )
      {
        continue;
      }
      else
      {
        ++counter;
      }
    }
  }
  return counter;
}
void words_list(string sent[], int total_sentences, int word_count, string words[][6])
{
  int count1 = 0, count2 = 0;
  char alpha = 0;
  for(int i=0; i<total_sentences; ++i)
  {
    for(int j=0; j<sent[i].length(); ++j)
    {
      alpha = sent[i][j];
      if( (alpha>64 && alpha<91) || (alpha>96 && alpha<123) )
      {
        words[count1][count2] = alpha;
        ++count2;
      }
      else
      {
        ++count1; 
        count2 = 0;
      }
    }
  }
}
void vocab(string words[][6], int word_count, string V[][6])
{
  bool present;
  int counter = 0;
  for(int i=0; i<word_count; ++i)
  {
    for(int j=0; j<6; ++j)
    {
      present = false; 
      for(int k=0; k<word_count; ++k)
      {
        if( (words[i][j]==V[k][j]) )
        {
          present = true;
          break; 
        }
        //else
        //{
          //present = false;
        //}
      }
      if(!present)
      {
        break;
      }
    }
    if(!present)
    {
      for(int x=0; x<6; ++x)
      {
        V[counter][x] = words[i][x];
      }
      ++counter;
    }
  }
}
 
 
