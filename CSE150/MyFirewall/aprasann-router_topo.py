#!/usr/bin/python

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.cli import CLI
from mininet.node import RemoteController

class final_topo(Topo):
  def build(self):

    switch2 = self.addSwitch('s2')
    switch1 = self.addSwitch('s1')
    switch3 = self.addSwitch('s3')

    self.addLink('s1', 's2', port1=1, port2=1)
    self.addLink('s1', 's3', port1=2, port2=4)
    self.addLink('s2', 's3', port1=2, port2=2)

    host1 = self.addHost('h1',mac='00:00:00:00:00:01',ip='20.1.1.5/24', defaultRoute="h1-eth1")
    host2 = self.addHost('h2',mac='00:00:00:00:00:02',ip='20.1.1.6/24', defaultRoute="h2-eth1")
    host3 = self.addHost('h3',mac='00:00:00:00:00:03',ip='30.0.1.1/24', defaultRoute="h3-eth1")
    host4 = self.addHost('h4',mac='00:00:00:00:00:04',ip='10.0.1.15/24', defaultRoute="h4-eth1")
    host5 = self.addHost('h5',mac='00:00:00:00:00:05',ip='10.0.1.16/24', defaultRoute="h5-eth1")


    self.addLink('s1', 'h2', port1=4, port2=1)
    self.addLink('s1', 'h1', port1=3, port2=1)
    self.addLink('s2', 'h4', port1=3, port2=1)
    self.addLink('s2', 'h5', port1=4, port2=1) 
    self.addLink('s3', 'h3', port1=3, port2=1) 


def configure():
  topo = final_topo()
  net = Mininet(topo=topo, controller=RemoteController)
  net.start()
  # use static ARP
  net.staticArp() 
  CLI(net)
  
  net.stop()


if __name__ == '__main__':
  configure()

