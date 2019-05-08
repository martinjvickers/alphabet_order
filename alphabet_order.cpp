#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <seqan/arg_parse.h>
#include <seqan/seq_io.h>
#include <map>

using namespace seqan;
using namespace std;

vector<map<char, int>> m;
map<char, int> m1 = {{'A', 65}, {'C', 67}, {'G', 71}, {'T', 84}};
map<char, int> m2 = {{'C', 65}, {'A', 67}, {'G', 71}, {'T', 84}};
map<char, int> m3 = {{'G', 65}, {'A', 67}, {'C', 71}, {'T', 84}};
map<char, int> m4 = {{'A', 65}, {'G', 67}, {'C', 71}, {'T', 84}};
map<char, int> m5 = {{'C', 65}, {'G', 67}, {'A', 71}, {'T', 84}};
map<char, int> m6 = {{'G', 65}, {'C', 67}, {'A', 71}, {'T', 84}};
map<char, int> m7 = {{'T', 65}, {'C', 67}, {'A', 71}, {'G', 84}};
map<char, int> m8 = {{'C', 65}, {'T', 67}, {'A', 71}, {'G', 84}};
map<char, int> m9 = {{'A', 65}, {'T', 67}, {'C', 71}, {'G', 84}};
map<char, int> m10 = {{'T', 65}, {'A', 67}, {'C', 71}, {'G', 84}};
map<char, int> m11 = {{'C', 65}, {'A', 67}, {'T', 71}, {'G', 84}};
map<char, int> m12 = {{'A', 65}, {'C', 67}, {'T', 71}, {'G', 84}};
map<char, int> m13 = {{'A', 65}, {'G', 67}, {'T', 71}, {'C', 84}};
map<char, int> m14 = {{'G', 65}, {'A', 67}, {'T', 71}, {'C', 84}};
map<char, int> m15 = {{'T', 65}, {'A', 67}, {'G', 71}, {'C', 84}};
map<char, int> m16 = {{'A', 65}, {'T', 67}, {'G', 71}, {'C', 84}};
map<char, int> m17 = {{'G', 65}, {'T', 67}, {'A', 71}, {'C', 84}};
map<char, int> m18 = {{'T', 65}, {'G', 67}, {'A', 71}, {'C', 84}};
map<char, int> m19 = {{'T', 65}, {'G', 67}, {'C', 71}, {'A', 84}};
map<char, int> m20 = {{'G', 65}, {'T', 67}, {'C', 71}, {'A', 84}};
map<char, int> m21 = {{'C', 65}, {'T', 67}, {'G', 71}, {'A', 84}};
map<char, int> m22 = {{'T', 65}, {'C', 67}, {'G', 71}, {'A', 84}};
map<char, int> m23 = {{'G', 65}, {'C', 67}, {'T', 71}, {'A', 84}};
map<char, int> m24 = {{'C', 65}, {'G', 67}, {'T', 71}, {'A', 84}};

struct ModifyStringOptions
{
   CharString string = NULL;
   CharString input_file = NULL;
};

seqan::ArgumentParser::ParseResult parseCommandLine(
	ModifyStringOptions & options, 
	int argc, 
	char const ** argv) {

   ArgumentParser parser("alphabet_order");
   addOption(parser, ArgParseOption("s", "string", 
                                    "The input string", 
                                    ArgParseArgument::INPUT_FILE,
                                    "IN"));
   addOption(parser, ArgParseOption("i", "input-file",
                                    "An input file",
                                    ArgParseArgument::INPUT_FILE,
                                    "IN"));

   setShortDescription(parser, "alphabet_order");
   setVersion(parser, "0.0.1");
   setDate(parser, "April 2019");
   addUsageLine(parser, "-i test.fasta \
                         [\\fIOPTIONS\\fP] ");
   addDescription(parser, "Lyndon factors based on Duval algorithm.");
   ArgumentParser::ParseResult res = parse(parser, argc, argv);

   if (res != ArgumentParser::PARSE_OK)
      return res;

   getOptionValue(options.string, parser, "string");
   getOptionValue(options.input_file, parser, "input-file");

   return ArgumentParser::PARSE_OK;
}

std::map<CharString, int> suffixArray(String<char> &dnaSeq)
{
   std::map<CharString, int> suffix_array;
   for(int i = 0; i < length(dnaSeq); i++)
   {
      suffix_array[suffix(dnaSeq, i)] = i;
   }
   return suffix_array;
}

int printArray(std::map<CharString, int> array)
{
   for(auto i : array)
      cout << i.first << "\t" << i.second << endl;
   return 0;
}

/*
This works by taking the vector position as a value for
order. So if a<b<c<d, and comparing a and d, then a is gt_eq d if 
pos_lhs <= pos_rhs.
*/
bool gt_eq(char &lhs, char &rhs, map<char, int> order)
{
   int pos_lhs, pos_rhs;

   if(order.find(lhs) == order.end())
      pos_lhs = (int)lhs;
   else
      pos_lhs = order[lhs];

   if(order.find(rhs) == order.end())
      pos_rhs = (int)rhs;
   else
      pos_rhs = order[rhs];

   if(pos_lhs >= pos_rhs)
      return true;
   else
      return false;
}

bool gt(char &lhs, char &rhs, map<char, int> order)
{
   int pos_lhs, pos_rhs;

   if(order.find(lhs) == order.end())
      pos_lhs = (int)lhs;
   else
      pos_lhs = order[lhs];

   if(order.find(rhs) == order.end())
      pos_rhs = (int)rhs;
   else
      pos_rhs = order[rhs];

   if(pos_lhs > pos_rhs)
      return true;
   else
      return false;
}

/*
  Based on;
  https://cp-algorithms.com/string/lyndon_factorization.html
*/
int duval(CharString text, StringSet<CharString> &results, map<char, int> order)
{
   size_t n = length(text);
   int h = 0;
   int words_count = 0;

   toUpper(text);

   while (h < n)
   {
      int i = h;
      int j = h + 1;

      //while (text[j] >= text[i]) 
      while(gt_eq(text[j], text[i], order))
      {
         //if(text[j] > text[i])
         if(gt(text[j], text[i], order))
            i = h;
         else
            i++;
         j++;
      }
      
      while (h <= i)
      {
         int spos = h;
         h += j - i;
         int epos = h;
         appendValue(results, infix(text, spos, epos));
      }
   }
   return words_count;
}

// A basic template to get up and running quickly
int main(int argc, char const ** argv)
{
   //parse our options
   ModifyStringOptions options;
   ArgumentParser::ParseResult res = parseCommandLine(options,argc, argv);
   if (res != ArgumentParser::PARSE_OK)
      return res == ArgumentParser::PARSE_ERROR;

   //open query file for the threads to read in batches
   SeqFileIn fastaFileIn;
   if(!open(fastaFileIn, (toCString(options.input_file))))
   {
      cerr << "Error: could not open file ";
      cerr << toCString(options.input_file) << endl;
      return 1;
   }

   m.push_back(m1);
   m.push_back(m2);
   m.push_back(m3);
   m.push_back(m4);
   m.push_back(m5);
   m.push_back(m6);
   m.push_back(m7);
   m.push_back(m8);
   m.push_back(m9);
   m.push_back(m10);
   m.push_back(m11);
   m.push_back(m12);
   m.push_back(m13);
   m.push_back(m14);
   m.push_back(m15);
   m.push_back(m16);
   m.push_back(m17);
   m.push_back(m18);
   m.push_back(m19);
   m.push_back(m20);
   m.push_back(m21);
   m.push_back(m22);
   m.push_back(m23);
   m.push_back(m24);

   CharString id, seq;
   while(!atEnd(fastaFileIn))
   {
      readRecord(id, seq, fastaFileIn);
      
      cout << "Number of factors new for " << id << endl;

      for(auto vloc : m)
      {
         StringSet<CharString> results;
         int word_count = duval(seq, results, vloc);

         int ints[] = {65, 67, 71, 84};
         for(auto i : ints)
         {
            for(auto v : vloc)
            {
               if(v.second == i)
                  cout << v.first << " < ";
            }
         }
         cout << " factors: " << length(results) << endl;

         int i = 0;
         for(auto r : results)
         {
            cout << "######### F-" << i << "\t" << length(r) << endl;
            if(length(r) < 101)
               cout << r << endl;
            i++;
         }
      }
   }

   return 0;
}
