
SET(BuildClassNamingRule ClassNaming)
BUILD_DYNAMIC_RULES("${BuildClassNamingRule}")

SET(BuildMethodNamingRule MethodNaming)
BUILD_DYNAMIC_RULES("${BuildMethodNamingRule}")

SET(BuildMethodUsageRule MethodUsage)
BUILD_DYNAMIC_RULES("${BuildMethodUsageRule}")

SET(BuildSpaceCheckRule SpaceCheck)
BUILD_DYNAMIC_RULES("${BuildSpaceCheckRule}")

SET(BuildVariableNameRule VariableName)
BUILD_DYNAMIC_RULES("${BuildVariableNameRule}")

SET(BuildBracesNewLineRule BracesNewLine)
BUILD_DYNAMIC_RULES("${BuildBracesNewLineRule}")
