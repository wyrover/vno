#-*- coding:utf-8 -*-
#!/usr/bin/env python

import logging

# from rpc import ControlServerHelper, CbmServerHelper, ThriftServerHelper
from rpc import CbmServerHelper, ThriftServerHelper
from rpc.RpcClient import *

def main():
    # ����logĬ�ϵĻ�������
    logging.basicConfig()
    
    # ����control������
    # ctrlHandler, ctrlServer = ControlServerHelper.create_server(HOST, PORT1)

    # ����service������
    handler, server = CbmServerHelper.create_server(HOST, PORT2)

    # ע��service�����������Ʒ���ӿ�
    # ctrlHandler.register(server)

    # ����һ���̸߳�service��������
    print '����service������(�˿�:9090)...'
    ThriftServerHelper.run_rpc_server(server, runThread=False)

    # �������Ʒ�����,����shutdown��Ϣ(���������߳�)
    print '����control������(�˿�:9100)...'
    # ThriftServerHelper.run_rpc_server(ctrlServer, runThread=False)
    
if __name__ == '__main__':
    main()