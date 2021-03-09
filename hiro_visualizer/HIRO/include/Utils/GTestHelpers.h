#ifndef UTILS_GTEST_HELPERS_H
#define UTILS_GTEST_HELPERS_H

#define GTEST_TEST_GLM_(expression, commands, actual, expected, fail) \
  GTEST_AMBIGUOUS_ELSE_BLOCKER_ \
  if (const ::testing::AssertionResult gtest_ar_ = \
      ::testing::AssertionResult(expression)); \
  else \
    fail(::testing::internal::GetBoolAssertionFailureMessage(\
        gtest_ar_, commands, actual, expected).c_str())

#define EXPECT_EQ_GLM(actual, expected) \
  GTEST_TEST_GLM_(glm_ext::AreEqual(actual, expected), std::string(std::string(#actual)+" and "+std::string(#expected)).c_str(), glm_ext::to_string(actual).c_str(), glm_ext::to_string(expected).c_str(), GTEST_NONFATAL_FAILURE_)


#define EXPECT_EQ_GLM_EPSILON(actual, expected, epsilon) \
  GTEST_TEST_GLM_(glm_ext::AreEqual(actual, expected, epsilon), std::string(std::string(#actual)+" and "+std::string(#expected)).c_str(), glm_ext::to_string(actual).c_str(), glm_ext::to_string(expected).c_str(), GTEST_NONFATAL_FAILURE_)

#endif /* !UTILS_GTEST_HELPERS_H */