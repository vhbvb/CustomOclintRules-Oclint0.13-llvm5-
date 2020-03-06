# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.oclint-0.13.1.Debug:
PostBuild.OCLintDriver.Debug: /Users/max/oclint_source-0.13.1/Driver_proj/bin/Debug/oclint-0.13.1
/Users/max/oclint_source-0.13.1/Driver_proj/bin/Debug/oclint-0.13.1:\
	/Users/max/oclint_source-0.13.1/Driver_proj/lib/Debug/libOCLintDriver.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAsmParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMInstrumentation.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMOption.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/usr/local/opt/openssl/lib/libssl.a\
	/usr/local/opt/openssl/lib/libcrypto.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMTransformUtils.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAnalysis.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMProfileData.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMObject.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMCore.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBinaryFormat.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMC.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMDemangle.a
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/bin/Debug/oclint-0.13.1


PostBuild.OCLintDriver.Debug:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/Debug/libOCLintDriver.a:
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/lib/Debug/libOCLintDriver.a


PostBuild.oclint-0.13.1.Release:
PostBuild.OCLintDriver.Release: /Users/max/oclint_source-0.13.1/Driver_proj/bin/Release/oclint-0.13.1
/Users/max/oclint_source-0.13.1/Driver_proj/bin/Release/oclint-0.13.1:\
	/Users/max/oclint_source-0.13.1/Driver_proj/lib/Release/libOCLintDriver.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAsmParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMInstrumentation.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMOption.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/usr/local/opt/openssl/lib/libssl.a\
	/usr/local/opt/openssl/lib/libcrypto.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMTransformUtils.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAnalysis.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMProfileData.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMObject.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMCore.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBinaryFormat.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMC.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMDemangle.a
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/bin/Release/oclint-0.13.1


PostBuild.OCLintDriver.Release:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/Release/libOCLintDriver.a:
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/lib/Release/libOCLintDriver.a


PostBuild.oclint-0.13.1.MinSizeRel:
PostBuild.OCLintDriver.MinSizeRel: /Users/max/oclint_source-0.13.1/Driver_proj/bin/MinSizeRel/oclint-0.13.1
/Users/max/oclint_source-0.13.1/Driver_proj/bin/MinSizeRel/oclint-0.13.1:\
	/Users/max/oclint_source-0.13.1/Driver_proj/lib/MinSizeRel/libOCLintDriver.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAsmParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMInstrumentation.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMOption.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/usr/local/opt/openssl/lib/libssl.a\
	/usr/local/opt/openssl/lib/libcrypto.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMTransformUtils.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAnalysis.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMProfileData.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMObject.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMCore.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBinaryFormat.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMC.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMDemangle.a
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/bin/MinSizeRel/oclint-0.13.1


PostBuild.OCLintDriver.MinSizeRel:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/MinSizeRel/libOCLintDriver.a:
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/lib/MinSizeRel/libOCLintDriver.a


PostBuild.oclint-0.13.1.RelWithDebInfo:
PostBuild.OCLintDriver.RelWithDebInfo: /Users/max/oclint_source-0.13.1/Driver_proj/bin/RelWithDebInfo/oclint-0.13.1
/Users/max/oclint_source-0.13.1/Driver_proj/bin/RelWithDebInfo/oclint-0.13.1:\
	/Users/max/oclint_source-0.13.1/Driver_proj/lib/RelWithDebInfo/libOCLintDriver.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAsmParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMInstrumentation.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMOption.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/usr/local/opt/openssl/lib/libssl.a\
	/usr/local/opt/openssl/lib/libcrypto.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMTransformUtils.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAnalysis.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMProfileData.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMObject.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMCore.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBinaryFormat.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMC.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a\
	/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMDemangle.a
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/bin/RelWithDebInfo/oclint-0.13.1


PostBuild.OCLintDriver.RelWithDebInfo:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/RelWithDebInfo/libOCLintDriver.a:
	/bin/rm -f /Users/max/oclint_source-0.13.1/Driver_proj/lib/RelWithDebInfo/libOCLintDriver.a




# For each target create a dummy ruleso the target does not have to exist
/Users/max/oclint_source-0.13.1/Driver_proj/lib/Debug/libOCLintDriver.a:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/MinSizeRel/libOCLintDriver.a:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/RelWithDebInfo/libOCLintDriver.a:
/Users/max/oclint_source-0.13.1/Driver_proj/lib/Release/libOCLintDriver.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAnalysis.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMAsmParser.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBinaryFormat.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMBitReader.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMCore.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMDemangle.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMInstrumentation.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMC.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMMCParser.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMObject.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMOption.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMProfileData.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMSupport.a:
/Users/max/oclint_source-0.13.1/build/llvm-install/lib/libLLVMTransformUtils.a:
/usr/local/opt/openssl/lib/libcrypto.a:
/usr/local/opt/openssl/lib/libssl.a:
