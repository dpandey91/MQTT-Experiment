#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

// Short alias for this namespace
namespace pt = boost::property_tree;

class Payload{

public:
  Payload();
  Payload(int nSeqNo);
  Payload(const std::string& aData, const std::string& aTopic, int nSeqNo);
  ~Payload();
  
  void setData(const std::string& aData);
  void setTopic(const std::string& aTopic);
  void setSeqNo(int nSeqNo);
  void setTimestamp(long aTimestamp);
  int getSeqNo();
  long getTimestamp();
  const std::string getString();
  void setDataInObject(std::string jsonString);

  void setValues(const std::string& aData, const std::string& aTopic, int nSeqNo);
  
private:
  std::string payloadData;
  std::string topic;
  int seqNo;
  
  //This timestamp value is in microseconds
  long timestamp;

  // Create a root
  pt::ptree root;
};

#endif //PAYLOAD_H

