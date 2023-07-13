# Lab 3 Skeleton
#
# Based on of_tutorial by James McCauley

from pox.core import core
import pox.openflow.libopenflow_01 as of

log = core.getLogger()

# msg = of.ofp_flow_mod()
# msg.match = of.ofp_match.from_packet(packet)

# msg.actions.append(of.ofp_action_output(port = <PORT>))
# msg.data = packet_in
# self.connection.send(msg)
class Firewall (object):
  """
  A Firewall object is created for each switch that connects.
  A Connection object for that switch is passed to the __init__ function.
  """
  def __init__ (self, connection):
    # Keep track of the connection to the switch so that we can
    # send it messages!
    self.connection = connection

    # This binds our PacketIn event listener
    connection.addListeners(self)

  def do_firewall (self, packet, packet_in):
    # The code in here will be executed for every packet.
    msg = of.ofp_flow_mod()
    ICMPproc = packet.find('icmp')
    ARPproc = packet.find('arp')
    IPV4proc = packet.find('ipv4')
    if ARPproc:
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
      msg.data = packet_in
      self.connection.send(msg)   
    elif ICMPproc:
      msg = of.ofp_flow_mod()
      msg.match = of.ofp_match.from_packet(packet)
      msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
      msg.data = packet_in
      self.connection.send(msg)
    elif IPV4proc:
      if IPV4proc.srcip == '20.1.1.10' and IPV4proc.dstip== '20.1.1.55' or IPV4proc.srcip == '20.1.1.55' and IPV4proc.dstip== '20.1.1.10' or IPV4proc.srcip == '20.1.1.11' and IPV4proc.dstip== '20.1.1.55' or IPV4proc.srcip == '20.1.1.55' and IPV4proc.dstip== '20.1.1.11' or IPV4proc.srcip == '20.1.1.55' and IPV4proc.dstip== '20.1.1.30':
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
        msg.data = packet_in
        self.connection.send(msg)
      elif IPV4proc.srcip == '20.1.1.55' and IPV4proc.dstip== '20.1.1.31' or IPV4proc.srcip == '20.1.1.31' and IPV4proc.dstip== '20.1.1.55':
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.actions.append(of.ofp_action_output(port = of.OFPP_FLOOD))
        msg.data = packet_in
        self.connection.send(msg)
      else:
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.data = packet_in
        self.connection.send(msg)
    else:
        msg = of.ofp_flow_mod()
        msg.match = of.ofp_match.from_packet(packet)
        msg.data = packet_in
        self.connection.send(msg)

    #print (packet_in)

  def _handle_PacketIn (self, event):
    """
    Handles packet in messages from the switch.
    """

    packet = event.parsed # This is the parsed packet data.
    if not packet.parsed:
      log.warning("Ignoring incomplete packet")
      return

    packet_in = event.ofp # The actual ofp_packet_in message.
    self.do_firewall(packet, packet_in)

def launch ():
  """
  Starts the component
  """
  def start_switch (event):
    log.debug("Controlling %s" % (event.connection,))
    Firewall(event.connection)
  core.openflow.addListenerByName("ConnectionUp", start_switch)
