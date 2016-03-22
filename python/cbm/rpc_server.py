#-*- coding:utf-8 -*-
#!/usr/bin/env python

import logging

# from rpc import ControlServerHelper, CbmServerHelper, ThriftServerHelper
from rpc import CbmServerHelper, ThriftServerHelper
from rpc.RpcClient import *

def main():
    # 采用log默认的基本配置
    logging.basicConfig()
    
    # 创建control服务器
    # ctrlHandler, ctrlServer = ControlServerHelper.create_server(HOST, PORT1)

    # 创建service服务器
    handler, server = CbmServerHelper.create_server(HOST, PORT2)

    # 注册service服务器到控制服务接口
    # ctrlHandler.register(server)

    # 单开一个线程给service服务器用
    print '启动service服务器(端口:9090)...'
    ThriftServerHelper.run_rpc_server(server, runThread=False)

    # 启动控制服务器,监听shutdown消息(会阻塞主线程)
    print '启动control服务器(端口:9100)...'
    # ThriftServerHelper.run_rpc_server(ctrlServer, runThread=False)
    
if __name__ == '__main__':
    main()