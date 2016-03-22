@echo off

thrift.exe --gen %1 cbm.thrift
rem thrift.exe --gen %1 ctrl.thrift