#include "Data.hpp"

#include <iostream>
#include <fstream>
using namespace std;


#include "macro.hpp"




Source::Source(string setpath,Types::StorageType setstorageType,Types::PathType setpathType,Types::DataType setdataType){
  path = setpath;
  storageType = setstorageType;
  pathType = setpathType;
  dataType = setdataType;
}

Source::Source(string setpath){
  path = setpath;
  storageType = Types::StorageType::ANY;
  pathType = Types::PathType::ANY;
  dataType = Types::DataType::ANY;
}

Source::Source(){
  path = "";
  storageType = Types::StorageType::NONE;
  pathType = Types::PathType::NONE;
  dataType = Types::DataType::NONE;
}


string Source::getVlcPath(){
  if (pathType == Types::PathType::URL){
    string out = path;
    out = ReplaceString(out,"&","%26");
    out = ReplaceString(out," ","%20");
    return out;
  }else{
    return path;
  }
}


void Playlist::saveLocally(){

};

void Playlist::shuffle(int startingOriginalIndex = -1){
  if (startingOriginalIndex == -1){

  }else{

  }
}