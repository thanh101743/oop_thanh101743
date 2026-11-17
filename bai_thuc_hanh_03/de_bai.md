Đề bài:
Nâng cấp bài toán ở bài trước bằng cách thay thế mảng tĩnh bằng mảng cấp phát động thông qua con trỏ.

Cấu trúc thiết kế:

Lớp Vehicle giữ nguyên

Lớp ParkingLot nâng cấp thành con trỏ:

Thuộc tính:
int parkID;
char size (S, M, L)
int capacity: sức chứa tối đa hiện tại (S = 1, M = 2, L = 3)
Vehicle** vehicles: Mảng con trỏ cấp phát động trên heap. Đây là con trỏ trỏ tới một mảng các con trỏ Vehicle* (hoặc Vehicle* vehicles cấp phát mảng đối tượng động)
int current VehicleCount: đếm số lượng xe thực tế đang đỗ
Phương thức:
Hàm khởi tạo ParkingLot(int id, char s): cấp phát động mảng con trỏ: vehicles = new Vehicles*[capacity], khởi tạo tất cả các ô bằng nullptr;
Hàm hủy ~ParkingLot: tự động duyệt và giải phóng từng đối tượng xe: delete vehicles[i] và giải phóng mảng con trỏ delete[] vehicles
Hàm khởi tạo sao chép & operator =: thực hiện sao chép sâu toàn bộ danh sách xe.
void resize(int newCapacity): hàm nội bộ tự động cấp phát mảng con trỏ
mới với newCapacity, sao chép các con trỏ cũ sang mảng mới, giải phóng mảng
cũ delete[] và cập nhật lại capacity.
bool addVehicle(const Vehicle &v):  Thêm xe vào ô trống. Nếu bãi đã đầy
(currentVehicleCount == capacity), tự động gọi resize(capacity * 2) trước
khi thêm.
bool removeVehicle(int vID): Tìm xe theo ID, gọi delete vehicles[i], dồn
mảng con trỏ và gán vị trí cuối cùng về nullptr.

Lớp 3: SystemInterface

Thuộc tính:
int lotCapacity: Sức chứa bãi đỗ tối đa hiện tại của hệ thống (Khởi tạo = 5).
int currentLotCount: Số lượng bãi đỗ hiện có trong hệ thống
ParkingLot** parkingLots: Mảng con trỏ động chứa các bãi đỗ xe.
Phương thức:
void runMenu()
Hàm khởi tạo: Cấp phát động mảng bãi đỗ: parkingLots = new ParkingLot*[lotCapacity]
Hàm hủy (~SystemInterface()): Giải phóng toàn bộ các bãi đỗ delete parkingLots[i]
và thu hồi mảng delete[] parkingLots.
void resizeSystem(int newCapacity): Mở rộng sức chứa bãi đỗ của hệ thống
khi vượt quá lotCapacity.

Yêu cầu:

 Bắt buộc sử dụng con trỏ thô (*), toán
tử cấp phát động new và giải phóng bộ nhớ delete / delete[]. (Chưa dùng
std::vector hay con trỏ thông minh std::unique_ptr)

QUY TẮC BA (RULE OF THREE): Tất cả các lớp quản lý bộ nhớ động
(ParkingLot, SystemInterface) bắt buộc phải cài đặt 3 phương thức đặc
biệt:
– Destructor (~Class()): Thu hồi toàn bộ vùng nhớ heap đã cấp phát khi
đối tượng bị hủy.
– Copy Constructor (Class(const Class&)): Thực hiện Sao chép sâu
(Deep Copy) khi khởi tạo đối tượng mới từ đối tượng cũ.
– Copy Assignment Operator (operator=): Thực hiện Sao chép sâu (Deep
Copy) khi gán hai đối tượng cho nhau.

AN TOÀN CON TRỎ: Mọi con trỏ chưa trỏ tới vùng nhớ hợp lệ phải được gán
giá trị nullptr. Sau khi delete, lập tức gán lại về nullptr để tránh lỗi Dangling
Pointer (con trỏ lơ lửng).

Thuật toán Tự động Mở rộng Sức chứa (Dynamic Resizing Algorithm):
• Khi thêm một xe vào bãi đầy, hệ thống không báo lỗi đầy bãi nữa mà tự động
nhân đôi capacity (capacity = capacity * 2), tạo mảng mới, chép dữ liệu cũ
sang và tiếp tục nhận xe mới.
Cơ chế Xóa dữ liệu An toàn (Safe Deletion):
• Khi xóa một xe khỏi bãi đỗ:
(a) Thu hồi bộ nhớ của đối tượng xe: delete vehicles[index];
(b) Dồn tất cả các con trỏ phía sau sang bên trái 1 vị trí.
(c) Gán ô con trỏ cuối cùng về nullptr: vehicles[currentVehicleCount - 1]
= nullptr;
(d) Giảm currentVehicleCount đi 1
Kiểm tra Rò rỉ Bộ nhớ (Memory Leak Check):
• Tất cả các khối lệnh new bắt buộc phải có khối lệnh delete tương ứng. Đảm
bảo khi người dùng chọn Thoát chương trình (Option 9), Destructor của
SystemInterface được kích hoạt để dọn dẹp sạch sẽ 100% bộ nhớ Heap.
