#-*- coding:utf-8 -*-
#!/usr/bin/env python

from thrift import Thrift
from thrift.transport import TSocket
from thrift.transport import TTransport
from thrift.protocol import TBinaryProtocol
from thrift.server import TServer

import threading

def make_rpc_server(processor, host='localhost', port=9090):
    transport = TSocket.TServerSocket(host=host, port=port)
    tfactory = TTransport.TBufferedTransportFactory()
    pfactory = TBinaryProtocol.TBinaryProtocolFactory()
    # 只能连接一个客户端
    # server = TServer.TSimpleServer(processor, transport, tfactory, pfactory)
    
    # You could do one of these for a multithreaded server
    # 每个客户端启动一个线程用于连接
    # server = TServer.TThreadedServer(processor, transport, tfactory, pfactory)
    
    # 连接线程池
    server = TServer.TThreadPoolServer(processor, transport, tfactory, pfactory)
    server.daemon = True #enable ctrl+c to exit the server
    server.setNumThreads(10);

    return server

def __run_rpc_server(server):
    server.serve()

# 运行服务器
def run_rpc_server(server, runThread=False):
    if runThread:
        t1 = threading.Thread(target=__run_rpc_server,args=(server,))
        t1.setDaemon(True)
        t1.start()
        return t1
    else:
        __run_rpc_server(server)
        return None