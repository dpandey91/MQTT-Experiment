#include "payload.h"

Payload::Payload():
  payloadData(),
  topic(),
  seqNo(0),
  timestamp(0),
  root()
{}

Payload::Payload(int nSeqNo):
  payloadData(),
  topic(),
  seqNo(nSeqNo),
  timestamp(0),
  root()
{}

Payload::Payload(const std::string& aData, const std::string& aTopic, int nSeqNo):
  payloadData(aData),
  topic(aTopic),
  seqNo(nSeqNo),
  timestamp(0),
  root()
{}

Payload::~Payload()
{}

void Payload::setData(const std::string& aData){
    payloadData = aData;
}

void Payload::setTopic(const std::string& aTopic){
    topic = aTopic;
}

void Payload::setSeqNo(int nSeqNo){
    seqNo = nSeqNo;
}

void Payload::setTimestamp(long aTimestamp){
    timestamp = aTimestamp;
}

int Payload::getSeqNo(){
    return seqNo;
}

long Payload::getTimestamp(){
    return timestamp;
}

const std::string Payload::getString(){
  root.put("data", payloadData);
  root.put("topic", topic);
  root.put("seqNo", seqNo);
  root.put("timestamp", timestamp);

  std::stringstream ssOut;
  boost::property_tree::write_json(ssOut, root);

  std::string outputStr = ssOut.str();
  return outputStr;
}

void Payload::setDataInObject(std::string jsonString){
    std::stringstream ssInput;
    ssInput << jsonString;
    boost::property_tree::read_json(ssInput, root);

   payloadData = root.get<std::string>("data");
   topic = root.get<std::string>("topic");
   seqNo = root.get<int>("seqNo");
   timestamp = root.get<long>("timestamp");
}

