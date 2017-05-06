#include "DataSet.h"
#include "gtest/gtest.h"

TEST(DataSetTest, TestPrepareData)
{
  const size_t expectedSize = 10000;
  DataSet dataSet(expectedSize, 10, 20);
  dataSet.PrepareData();

  EXPECT_EQ(expectedSize, dataSet.m_size);
}
