@echo off
del /q ..\common\proto\*
del /q ..\go\eqproto\*
protoc --cpp_out=../common/proto --go_out=../go/eqproto message.proto