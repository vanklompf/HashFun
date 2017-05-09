#ifndef HASHFUNCTIONENTRY_H_
#define HASHFUNCTIONENTRY_H_

#include <cstdint>
#include <string>
#include <type_traits>
#include <vector>

using HashFunc = std::add_pointer<uint32_t(const uint8_t*, int)>::type;

struct HashFunctionEntry
{
  const std::string name;
  const HashFunc func;
  std::vector<uint32_t> results;
};

using HashFunctionsSet = std::vector<HashFunctionEntry>;

#endif /* HASHFUNCTIONENTRY_H_ */
