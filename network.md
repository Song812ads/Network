## OSI - LAN - WAN - TCP/IP Network:
#

1. Mô hình OSI:

OSI(Open System Interface) là 1 mô hình diễn tả cách để thông tin từ phần mềm của 1 máy tính truyền qua phần mềm ở máy tính khác thông qua 1 lớp vật lý. Mô hình được ra đời năm 1984 và trở thành mô hình mang tính kiến trúc, được sử dụng chủ yếu trong học thuật để hiểu về vấn đề. Mô hình gồm 7 lớp. 
![Alt text](image-3.png)

* Lớp Physical:

 Tầng vật lý là hạ tầng cơ sở của mạng truyền thông, cung cấp phương tiện truyền tín hiệu thô sơ ở dạng bit.

Thông thuồng sẽ có 2 loại kết nối là Guided Media và Unguided media:
*  With guided
media, the waves are guided along a solid medium, such as a fiber-optic cable, a twisted-pair copper
wire, or a coaxial cable. 
* With unguided media, the waves propagate in the atmosphere and in outer
space, such as in a wireless LAN or a digital satellite channel.

Một số Guided Media (cáp) thông thường sử dụng:

* Twisted-pair copper wire: Đây là loại rẻ nhất và thông thường đươc sử dụng hiện tại. Data rates for
LANs using twisted pair today range from 10 Mbps to 10 Gbps. Được sử dụng trong kết nối mạng LAN hay trong công nghệ DSL 
* Coaxial Cable: Thường được sử dụng nhiều trong cáp TV hay cáp kết nối Internet, tốc độ đạt được 10Mbps
![Alt text](image-1.png)
* Fiber Optics: An optical fiber is a strand of glass that is as thin as a human hair. This strand is designed to carry information using pulses of light emitted by a laser. An optical fiber is a complex structure that consists of three layers.
![Alt text](image-2.png)
https://www.coherent.com/news/glossary/optical-fibers

Một số Unguided Media thông thường được sử dụng:
* Terrestrial radio channels can be broadly classified into three groups: those that operate over very short
distance (e.g., with one or two meters); those that operate in local areas, typically spanning from ten to a few hundred meters.
* Sattelite Radio Channels: A communication satellite links two or more Earth-based microwave transmitter/ receivers, known as
ground stations. There are 2 types: geostationary satellites and low-earth orbiting. 

#

* Lớp Data-Link:

Lớp này đảm bảo cho thông tin truyền tải từ network-layer datagram mà không xảy ra lỗi. Nó cung cấp các phương thức đáng tin cậy để giao tiếp giữa các device. Nó chịu trách nhiệm cho việc định danh các thiết bị khi làm việc trên mạng LAN.

Các nhiệm vụ chính của lớp Data-link là:

* **Framing**: Almost all link-layer protocols encapsulate each network-layer datagram within a link-layer
frame before transmission over the link. A frame consists of a data field, in which the network-layer
datagram is inserted, and a number of header fields.
* **Link access**: A medium access control (MAC) protocol specifies the rules by which a frame is
transmitted onto the link. For point-to-point links that have a single sender at one end of the link and
a single receiver at the other end of the link, the MAC protocol is simple (or nonexistent)—the sender
can send a frame whenever the link is idle. 
* **Reliable delivery**: When a link-layer protocol provides reliable delivery service, it guarantees to
move each network-layer datagram across the link without error. Recall that certain transport-layer
protocols (such as TCP) also provide a reliable delivery service. Similar to a transport-layer reliable
delivery service, a link-layer reliable delivery service can be achieved with acknowledgments and
retransmissions
* **Error Control**: Error control is achieved by adding a calculated value CRC (Cyclic Redundancy Check) that is placed to the Data link layer's trailer which is added to the message frame before it is sent to the physical layer. If any error seems to occurr, then the receiver sends the acknowledgment for the retransmission of the corrupted frames. 

Một số ví dụ về các thiết bị và công nghệ ở lơp DataLink: 

_ DSL: 
![Alt text](song/image-14.png)

_ PON:
![Alt text](song/image-15.png)

_Ethernet Switch: 
![Alt text](song/image-17.png)
#
* Lớp Network:

Đây là lớp xác định địa chỉ lớp 3 của các thiết bị, xác định vị trí các thiết bị trên mạng lưới. Nó cũng xác định đường đi ngắn nhất dựa vào các điều kiện của mạng lưới. Phương thức chủ yếu trong lớp này là ip và ipv6. Hai nhiệm vụ chính của lớp này là:

* **Forwarding**. When a packet arrives at a router’s input link, the router must move the packet to the
appropriate output link. 
* **Routing**. The network layer must determine the route or path taken by packets as they flow from a
sender to a receiver.

2 nhiệm vụ này được thực hiện thông qua forwarding table với 2 tác vụ khác là Control plane (routing) và Data plane (forwarding).
![Alt text](song/image-20.png)
https://blog.ipspace.net/2013/08/management-control-and-data-planes-in.html

Mục đích cần phải đạt được trong lớp này là:

_ **Guaranteed delivery**. This service guarantees that a packet sent by a source host will eventually
arrive at the destination host.

_ **Guaranteed delivery with bounded delay**. This service not only guarantees delivery of the packet,
but delivery within a specified host-to-host delay bound (for example, within 100 msec).

_ **In-order packet delivery**. This service guarantees that packets arrive at the destination in the order
that they were sent.

_ **Guaranteed minimal bandwidth**. This network-layer service emulates the behavior of a
transmission link of a specified bit rate (for example, 1 Mbps) between sending and receiving hosts.
As long as the sending host transmits bits (as part of packets) at a rate below the specified bit rate,
then all packets are eventually delivered to the destination host.

_ **Security**. The network layer could encrypt all datagrams at the source and decrypt them at the
destination, thereby providing confidentiality to all transport-layer segments.

2 thiết bị phổ biến sử dụng trong lớp này là Router và Switch layer-3

#
* Lớp Transport: 

Nhiệm vụ chính của lớp này là đảm bảo dữ liệu được truyền đi hoàn toàn. Nó nhận dữ liệu từ các lớp trên và chuyển thành dữ liệu nhỏ hơn gọi là segments.

2 phương thức chủ yếu trong lớp này là TCP và UDP:

_ TCP (Transmission Control Protocol): phương thức tiêu chuẩn để hệ thống có thể kết nối với Internet, và giao tiếp giữa các host. Các segments đươc chuyển dịch qua Internet theo nhiều đường đi và các trật tự khác nhau để đến điểm đích. Lớp này sẽ tiếp tục định hướng đường đi kế tiếp của packet.<br>
_ UDP (User Datagram Protocol): Đây là phương thức không đáng tin cậy 

Chức năng của lớp Transport:

_ **Service-point addresssing**: máy tính có thể chạy nhiều chương trình cùng lúc, dữ liệu sẽ được truyền không chỉ là từ máy này sang máy khác mà có thể từ process này sang process khác. Lớp transport sẽ thêm vào header 1 địa chỉ gọi là service-point address hay là port address.<br>
_ **Segmentation and reassembly**: khi lớp Transport nhận được dữ liệu từ cac lớp trên, chúng sẽ chia dữ liệu thành các segments nhỏ với các số đại diện cho các segment đó. Khi dữ liệu đến đích, các segments sẽ được tái kết hợp dựa trên số đại diện.<br>
_ **Connection Control**: Transport layers cung cấp 2 dịch vụ là Connection-oriented và Connectionless. Connectionless sẽ xem các segment là các packet riêng biệt và truyền đến điểm đích. Connection-oriented sẽ kết nối với điểm đích trước rồi mới truyền các packets.<br>
_ **Flow Control**: Chịu trách nhiệm cho việc truyền tải end-to-end. <br>
_ **Error Control**: Lớp transport sẽ đảm bảo dữ liệu sẽ truyền đến điểm đích mà không xảy ra lỗi.

* Lớp Session:

Đây là lớp công bố, duy trì, động bộ 2 process đang truyền dữ liệu với nhau.

Chức năng của lớp Session: <br>
_ **Dialog Control**: Nó sẽ tạo ra 1 hộp thoại giao tiếp giữa các process
![Alt text](image-4.png)<br>
_ **Synchronization**: Lớp session sẽ thêm 1 checkpoint để kiểm tra. Nếu có lỗi diễn ra trong quá trình truyền, việc truyền sẽ được khởi động lại tại thời điểm checkpoint. Quá trình này được gọi là Synchronization and recovery.

* Lớp Presentation: 

Lớp này sẽ xác định các vấn đề về syntax và semantics của thông tin chuyển giữa 2 systems. Nó làm việc như 1 bộ giải mã thông tin và chuyển data từ 1 dạng file này sang file khác.

Chức năng của lớp Presentation:

_**Translation**: Process trong 2 hệ thống sẽ chuyển giao thông tin với nhau theo 1 form nhất định. <br>
_**Encryption**: Đây là hoạt động cần thiết để duy trì bảo mật. Mã hóa là quá trình chuyển form dữ liệu gốc sang 1 form khác thuận tiện cho việc truyền thông tin hơn.<br>
_**Compression**: Đây là bước giải mã các thông tin đã được mã hóa

* Lớp Application:

Đây là lớp gần nhất với người dùng, sẽ tạo ra 1 cửa sổ giao diện để người dùng truy cập các dịch vụ trên mạng. Nó chịu trách nhiệm cho tính minh bạch của mạng và phân bố các tài nguyên.

Một số dịch vụ có thể kể đến như:<br>
_**File transfer, access and management**: truy cập file trên remote
_**Mail service**: Cung cấp chức năng chuyển tiếp email và lưu trữ
_**Directory service**: cung cấp 1 kho dữ liệu phân tác và được dùng để cung cấp những thông tin global về các đối tượng.

2. Mô hình TCP/IP Network: 

The TCP/IP model defines how devices should transmit data between them and enables communication over networks and large distances. The model represents how data is exchanged and organized over networks.

Mô hình gồm 4 hoặc 5 lớp. 2 lớp đầu có thể kết hợp lại gọi là lớp Access Network. Nhìn chung các lớp ở TCP/IP khá tương đồng về mặt chức năng với mô hình OSI. Một điểm nổi bật là các lớp TCP/IP lại củ thể hơn về mặt giao thức và cách vận hành.

![Alt text](image-5.png)

* Lớp Access Network:

Nhìn chung lớp này khá tương đồng 2 lớp đầu tiên trong mô hình OSI. Một số phương thức được dùng trong lớp này như Ethernet, token ring, FDDI, X.25, frame relay,...

* Lớp Network:

Mục đích chính của lớp này là đưa dữ liệu packets từ bất kì network nào và nó sẽ đến vị trí đích mà nó cần phải đến.

Một số phương thức để thực hiện điều này có thể kế dến:<br>
_ IP protocol: phương thức này tương tự phương thức trong mô hình OSI<br>
_ ARP (Address Resolution Protocol): đây là phương thức sẽ xác định địa chỉ vật lý (địa chỉ MAC) từ các địa chỉ IP
_ ICMP (Internet Control Message Protocol): đây là phương thức mà host và router sẽ gửi thông báo dựa trên vấn đề của datagram được chuyển đi về nơi phát. Datagram sẽ được chuyển router-to-router cho đến khi đến điểm đích. Nếu trong quá trình vận chuyển có lỗi, router sẽ ngay lập tức báo lỗi về nguồn phát.

* Lớp Transport:

Cũng tương tự như mô hình OSI gồm 2 giao thức chính là TCP và UDP

* Lớp Application:

Nếu người dùng muốn tương tác với ứng nhiều hệ thống mạng, lớp này sẽ cung cấp các giao thức tương tác với ứng dụng như data encoding, data translation và provisions.

Các phương thức được sử dụng chủ yếu trong lớp này là: 

https://www.tutorialspoint.com/what-is-application-layer-protocols-in-tcp-ip


* Sự khác biệt giữa mô hình TCP/IP và OSI:

Đầu tiên, OSI là 1 mô hình mang tính lý thuyết và thiên về để tìm hiểu cách 1 máy tính nhận và xử lý dữ liệu thế nào. Mô hình TCP/IP là mô hình được sử dụng nhiều trong các giao thức liên quan đến kết nối mạng.

Tiếp đến, số lớp Layer của mô hình TCP/IP ít hơn mô hình OSI. Đó là do sự kết hợp của nhiều lớp vào 1 lớp.
Vơi việc nhiều lớp cần thiết hơn, yêu cầu về phần cứng và các công cụ cũng là nhiều hơn. Số bit và thông tin cần xử lý khi đó cũng ít hơn.

![Alt text](image-29.png)
(OSI Flow)

![Alt text](image-30.png) (TCP/IP Flow)

Một điểm kém hơn giữa TCP/IP so với OSI, đó là TCP/IP cung cấp phương thức Connectionless(UDP) đồng thời Connection-Oriented(TCP) cho viêc truyền tải còn OSI là Connection-Oriented. Do đó, khi sử dụng phương thức TCP/IP người dùng cần cân nhắc phương thức phù hợp.

Mô hình OSI là mô hình ra sau mô hình TCP/IP và là 1 mô hình lý thuyết. OSI có thể là 1 mô hình khi phát triển đến tối ưu sẽ là hiệu quả hơn TCP/IP. Tuy nhiên, việc nghiên cứu và tạo ra thêm các phần cứng phù hợp với các yêu cầu của các lớp của OSI có thể sẽ đòi hỏi nhiều yêu tài nguyên hơn nhưng không chắc mang lại nhiều hiêu quả hơn TCP/IP.

3. LANs:

Mạng LAN (Local Network Area) hay còn gọi là mạng cục bộ. Mạng LAN được hiểu là sự kết hợp của nhiều các thiết bị được kết nối lại với nhau trong một hệ thống mạng tại một khu vực nhất định (ví dụ như công ty, phòng làm việc, trường học, nhà riêng,...). Việc ghép nối các thiết bị này trong cùng một hệ thống cho phép các thiết bị này có thể trao đổi dữ liệu với nhau một cách nhanh chóng và dễ dàng hơn (chia sẻ tập tin, hình ảnh, …).

* Link Layer Addressing và ARP:

a. Link Layer Addressing:

Link-layer address(hay được gọi với LAN address,
physical address, MAC address) được lưu trong adapters (network interfaces).

_ An adapter’s MAC address has a flat structure (as opposed to a hierarchical structure) and doesn’t
change no matter where the adapter goes.<br> _When an adapter wants to send a frame to some destination adapter, the sending adapter inserts the
destination adapter’s MAC address into the frame and then sends the frame into the LAN.<br>_Thus, an adapter may receive a frame that isn’t
addressed to it. Thus, when an adapter receives a frame, it will check to see whether the destination
MAC address in the frame matches its own MAC address.<br> _If there is a match, the adapter extracts the
enclosed datagram and passes the datagram up the protocol stack. If there isn’t a match, the adapter
discards the frame, without passing the network-layer datagram up.<br> _
However, sometimes a sending adapter does want all the other adapters on the LAN to receive and
process the frame it is about to send. In this case, the sending adapter inserts a special **MAC broadcast
address** into the destination address field of the frame

b. ARP:

Because there are both network-layer addresses  and link-layer
addresses, there is a need to translate between them. For the Internet, this is
the job of the Address Resolution Protocol (ARP).

(*Lý do cần sử dụng và chuyển hóa sang địa chỉ MAC: do tồn tại nhiều loại network-layer address, tốn dung lượng RAM khi phải lưu và thay đổi khi thay đổi vị trí)

Quá trình thực hiện: <br>
_ Ban đầu, sau khi ARP resolve địa chỉ IP từ điểm gốc, 1 ARP packet sẽ được gửi đi từ điểm bắt đầu đến điểm kết thúc, để xác định địa chỉ MAC của điểm đich. Những địa chỉ MAC này sẽ được lưu vào ARP table để tiếp tục sử dụng trong 1 thời gian TTL<br>
_ Sau khi nhận được địa chỉ đích từ các điểm đến, adapter sẽ tạo 1 link-layer frame chứa MAC address điểm đích và gửi frame ấy lên LAN.

Một vài điểm lưu vê ARP:<br>
_ ARP message sẽ được gửi trong 1 broadcast frame và trả lời với 1 standard frame.  <br>_ ARP is plug-and-play; that is, an ARP
table gets built automatically—it doesn’t have to be configured by a system administrator. <br>_ If a host
becomes disconnected from the subnet, its entry is eventually deleted from the other ARP tables in the
subnet.

* Ethernet: 

Ethernet là công nghệ LAN tốc độ cao sớm nhất được ra mắt, với giá thành rẻ và không phức tạp. Những sản phầm của Ethernet càng ngày càng cải thiện về data rates. 

Cấu trúc 1 frame của Ethernet: 
![Alt text](song/image-27.png)

* Switched LANs:

Cách Switch vận hành: <br>
_ Forwarding and filtering: 

Filtering is the switch function that determines whether a frame should be forwarded to some interface
or should just be dropped. <br>Forwarding is the switch function that determines the interfaces to which a
frame should be directed, and then moves the frame to those interfaces.

_ Self Learning: 

Ban đầu switch table sẽ hoàn toán trống <br>
Với mỗi incoming frame, switch sẽ lưu vào MAC table (1)địa chỉ MAC điểm gốc, (2) số lượng kết nối (3) thời gian hiện tại. 
![Alt text](song/image-28.png)
Switch sẽ tự động xóa địa chỉ nếu địa chỉ đó không được nhận hoặc gửi trong 1 khoảng thời gian. 

Đặc điểm của Switched LANs:

_ **Elimination of Collision**: The switches buffer frames and never transmit more than one frame on
a segment at any one time. As with a router, the maximum aggregate throughput of a switch is the
sum of all the switch interface rates. Thus, switches provide a significant performance improvement
over LANs with broadcast links.<br>
_ **Heterogenous links**: Because a switch isolates one link from another, the different links in the
LAN can operate at different speeds and can run over different media.<br>
_ **Management**: For example, if an adapter malfunctions and continually
sends Ethernet frames (called a jabbering adapter), a switch can detect the problem and internally
disconnect the malfunctioning adapter.


* Virtual LANs:

Một số hạn chế của Switch LANs có thể kể đến là:<br> 
_ **Lack of traffic isolation**: LAN có thể xác định là truyền trong 1 broadcast, tuy nhiên có những thiết bị không cần truyền đến trong mạng<br>
_ **Inefficient use of switches**: xảy ra khi số lượng người là quá nhiều so với port có sẵn<br>
_ **Managing errors**: Khi có nhiều nhóm và các thành viên, việc chuyển giao các thành viên cũng sẽ dẫn đến việc thay đổi ở Switch cho phù hợp.<br>
Virtual VLANs có thể giải quyết những vấn đề trên. 

VLANs allows multiple virtual local
area networks to be defined over a single physical local area network infrastructure. Hosts within a
VLAN communicate with each other as if they (and no other hosts) were connected to the switch. In a
port-based VLAN, the switch’s ports (interfaces) are divided into groups by the network manager. Each
group constitutes a VLAN, with the ports in each VLAN forming a broadcast domain.

* Wireless LANs:

Wireless LANs là 1 trong những công nghệ kết nối mạng phổ biến nhất hiện nay với tiêu chuẩn IEEE 802.11 hay được biết đến là Wifi

The
fundamental building block of the 802.11 architecture is the basic service set (BSS). A BSS contains
one or more wireless stations and a central base station, known as an access point (AP) 

* Secured Wireless LANs:

Trong các vấn đề bảo mật trong việc truyền dữ liệu, có 2 phương thức được sử dụng nhiều nhất hiện này là WEP và WPA (dựa theo tiêu chuẩn 802.11i)

Thuật toán giải mã dữ liệu WEP:

![Alt text](song/image-22.png)

![Alt text](song/image-23.png)

4. WANs:


![Alt text](image-24.png)

a. Switched WANs:

b. Point-to-point WANs:

c. SD-WAN:

https://www.networkacademy.io/ccie-enterprise/sdwan/why-do-we-need-sd-wan

https://www.networkacademy.io/ccie-enterprise/sdwan/what-is-sd-wan

https://www.researchgate.net/publication/365785923_Comparative_Study_of_WAN_Services_and_Technologies_in_Enterprise_Business_Networks


## Transport Layer_TCP Protocol_UDP Protocol:
#
1. Transport Layer: 
