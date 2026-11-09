Đề bài:

Nâng cấp bài toán ở bài số 1 bằng việc thay thế toàn bộ các biến đối tượng lẻ (vehicle 1 2 3, lot 1 2 3) bằng các mảng tĩnh

Cấu trúc thiết kế:

Lớp Vehicle giữ nguyên
Lớp ParkingLot nâng cấp thành mảng tĩnh:
+ Thuộc tính:
    - int parkID;
    - char size (S, M, L)
    - static const int MAX_VEHICLES = 3
    - Vehicle vehicles\[MAX_VEHICLES]: mảng tĩnh chứa các Vehicle.
    - int current VehicleCount: đếm số lượng xe thực tế đang đỗ
+ Phương thức:
    - bool isFull() const: kiểm tra đầy
    - bool addVehicle(const Vehicle &v): Thêm xe vào vị trí vehicles[currentVehicleCount), tăng currentVehicleCount lên 1
    - bool removeVehicle(int vID): Xóa xe theo ID, giảm currentVehicleCount đi 1
    - int findVehicleIndex(int vID) const: trả về chỉ số của xe trong mảng (-1 nếu không tìm thấy)
    - void displayLotInfo() const: in thông tin bãi và danh sách các xe (duyệt mảng)

Lớp 3: SystemInterface
+ Thuộc tính:
    - static const int MAX_LOTS: từ 3 lên 10 bãi
    - ParkingLot parkingLots\[MAX_LOTS]: mảng tĩnh chứa các ParkingLot
    - int currentLotCount: số lượng bãi đỗ hiện có (khởi tạo = 0)
+ Phương thức:
    - void runMenu()
    - bool isParkIDExists(int pID) const: kiểm tra trùng bãi đỗ
    - bool isVehicleIDExists(int vID) const: kiểm tra trùng phương tiện
    - int generateRandomID(): hàm sinh ID ngẫu nhiên nếu nhập trùng

---

Yêu cầu:
- Thuật toán dồn mảng sang trái khi xóa xe hoặc bãi xe trong mảng tương ứng;
- Khi thêm xe mới hệ thống tìm bãi đỗ đầu tiên còn trống để xếp vào. Nếu đã đầy tất cả thì cảnh báo ra màn hình.
- Xử lý trùng ID bãi đỗ và phương tiện: nhập ID đã tồn tại trong mảng, hiển thị cảnh báo và dùng hàm generate ID ngẫu nhiên
- Catch lỗi std::cin.fail(), xóa cờ lỗi std::cin.clear(), loại bộ nhớ đệm std::cin.ignore(), yêu cầu nhập lại.
