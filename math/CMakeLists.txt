# 查找当前目录下的所有源文件
# 并将名称保存到DIR_LIB_SRCS变量
aux_source_directory(. DIR_LIB_SRCS)

# 将该目录下的源文件编译成静态链接库
add_library(MathFunctions ${DIR_LIB_SRCS})

# # 指定MathFunctions库安装的路径
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)