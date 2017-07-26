#include "Global_MessageId.h"


Global_MessageId* Global_MessageId::instance = 0;

Global_MessageId* Global_MessageId::getInstance()
{
  if(instance==0) instance = new Global_MessageId();
  return instance;
}
int Global_MessageId::getId()
{
  return this->msgId;
}
int Global_MessageId::getNextId()
{
  return this->msgId++;
}
void Global_MessageId::setId(int id)
{
  this->msgId = id;
}
Global_MessageId::Global_MessageId()
{
  this->msgId = 0;
}