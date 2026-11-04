# Hạn chế bắt buộc
---
\- Đặt scope các thuộc tính trong class là private;
\- Đặt scope các phương thức trong class là public;

\- Không dùng mảng và con trỏ;
\- Số lượng đối tượng cố định qua các biến đối tượng đơn lẻ và biến cờ trạng thái;


# Thiết lập class
---

## Vehicle
---
#### Thuộc tính
\- int vehicleID;
\- string vehicleType;
\- int entryTime;
\- int ParkingDuration;
\- double parkingFee;
\- bool isOccupied;
#### Phương thức
\- Constructor mặc định & có tham số;
\- Get, Setters tất cả thuộc tính;
\- void calculateFee() tính phí
\- void display() in ra màn hình

## ParkingLot
---
#### Thuộc tính
\- int parkID;
\- char size;
\- Vehicle vehicle1, Vehicle vehicle2, Vehicle vehicle3;
\- bool hasVehicle1, bool hasVehicle2, bool hasVehicle3;
#### Phương thức
\- Constructor mặc định & có tham số theo ParkID và Size;
\- bool addVehicle (const Vehicle &v): thêm xe theo sức chứa;
\- bool removeVehicle(int vID): Xóa xe khỏi bãi;
\- void displayLotInfo(): hiện ID bãi, kích thước, liệt kê các xe hiện có.

## SystemInterface
---
#### Thuộc tính
\- ParkingLot parkingLot1, parkingLot2, parkingLot3;
\- bool hasLot1, hasLot2, hasLot3;
#### Phương thức
\- main() và xử lý nhập xuất
\- void runMenu(): hiện menu, điều phối chức năng ctrinh.

# Tính phí đỗ xe
---
(trên giờ)
Car: $6.00
Motorcycle: $4.00
Bicycle: $2.00

Giờ cao điểm: 6~9h và 15~18h.

Công thức tính phí:
2 giờ đầu: vào giờ cao điểm tăng 30%, thấp điểm giảm 5%

từ giờ thứ 3 giảm 10% cho mọi khung giờ

# Yêu cầu chức năng menu
---

Hiển thị menu lặp lại liên tục đến khi người dùng chọn thoát:
1. Tạo bãi đỗ xe mới. Nhập parkID và size. Có kiểm tra trùng ID hoặc quá sức chứa
2. Thêm xe vào bãi: nhập thông tin xe, tự động xếp và tính parkingFee.
3. Xóa bãi đỗ: nhập parkID
4. Lấy xe ra khỏi bãi: nhập vehicleID
5. Hiển thị danh sách tất cả bãi đỗ: liệt kê ID, kích thước, số xe
6. Hiển thị danh sách xe theo bãi cụ thể: qua parkID, in ra chi tiết từng xe trong bãi.
7. Liệt kê xe theo loại phương tiện: nhập loại phương tiện in ra xe loại tương ứng và bãi đỗ tương ứng
8. Xem báo cáo tóm tắt phí đỗ xe trung bình: tính và hiển thị phí đỗ xe trung bình cho từng loại trên toàn hệ thống và phân tích chi tiết theo từng bãi đỗ.
9. Thoát chương trình
