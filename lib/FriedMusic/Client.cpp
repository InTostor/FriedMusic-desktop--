#include "Client.hpp"
#include <iostream>
#include <string>
#include "macro.hpp"
#include <filesystem>
#include "cpr/cpr.h"

using namespace std;

Client::Client()
{
	
}

void	Client::authenticate()
{
	
}

string Client::getUsername()
{
	return (this->_username);
}

bool Client::isServerAccessible()
{
	return false;
}

bool	Client::isAuthenticated()
{
	return false;
}

void	Client::downloadDatabase()
{
	
}

void	Client::pullRemote()
{
	
}

void	Client::pushRemote()
{
	
}

void	Client::downloadTrack(vector<string> filenames)
{
	
}

void	Client::downloadTrack(string filename)
{
	
}

Source	Client::lookupTrack(string filename)
{

  string localPath = getConfigValue("localMusicStorage");
  if (filesystem::exists(localPath)){
    Source source(localPath,Types::StorageType::LOCAL,Types::PathType::FILESYSTEMPATH,Types::DataType::TRACK);
    return source;
  }

  string remoteUrl = getConfigValue("musicStorageUrl") + filename;
  cpr::Response response = cpr::Head(cpr::Url(remoteUrl));
  if (response.status_code == 200){
    Source source(remoteUrl,Types::StorageType::REMOTE,Types::PathType::URL,Types::DataType::TRACK);
    return source;
  }
    Source source;
    return source;
}


void	Client::assembleTrack(Track *track)
{
	
}

void	Client::assembleTrack(vector<reference_wrapper<Track>> tracks)
{
	vector<string> originalFilenames;
  string sql;

  for (int i=0; i<tracks.size(); i++){
    originalFilenames.insert(
      originalFilenames.begin()+i,
      filesystem::path(tracks[i].get().filename)
      );
  }  
  if (databaseType == Types::StorageType::LOCAL){
    sql.append(" SELECT * FROM fullmeta WHERE filename in (");
    sql.append(join(originalFilenames,","));
    sql.append(")");
  }else{
    sql.append("WHERE filename IN (");
    sql.append(join(originalFilenames,","));
    sql.append(")");
  }
}