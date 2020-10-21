project(WorkflowExecutor)

add_executable(WorkflowExecutor main.cpp Blocks.cpp Blocks.h Parser.cpp Parser.h Validator.cpp Validator.h
        Executor.cpp Executor.h)