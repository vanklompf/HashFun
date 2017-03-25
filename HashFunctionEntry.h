#ifndef HASHFUNCTIONENTRY_H_
#define HASHFUNCTIONENTRY_H_

using HashFunc = std::add_pointer<uint32_t(const uint8_t*, int)>::type;

struct HashFunctionEntry
{
  const std::string name;
  const HashFunc func;
  uint32_t result;
};

using HashFunctionsSet = std::vector<HashFunctionEntry>;

#endif /* HASHFUNCTIONENTRY_H_ */
