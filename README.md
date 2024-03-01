# LTNC2022_UET_Nhom16_PixelAdventure
***PHÂN CÔNG CÔNG VIỆC**
1. Tống Minh Trí(Nhóm trưởng):
* Xây dựng khung cho game
* Thiết kế ảnh cho game
* Làm phần di chuyển cho nhân vật, check va chạm với map
* Làm phần chuyển trạng thái của game (Menu, Instruction, Rank, ....)
* Chỉnh sửa và ghép code, fix bugs và lỗi tràn bộ nhớ
* Làm video giới thiệu game

2. Lê Văn Bảo:
* Tạo và xây dựng hình ảnh, các chướng ngại vật trong game (hoa quả, gai, đá gai, ...)
* Làm phần Rank và lưu dữ liệu người chơi
* Làm phần check va chạm với chướng ngại vật
* Chỉnh sửa phần nhập tên để phù hợp với game 
* Chỉnh sửa và ghép code 

3. Dương Quang Minh:
* Thiết kế map
* Tạo và xây dựng hình ảnh trong game (hoa quả), các chướng ngại vật di chuyển(lưỡi cưa, kẻ địch, ...)
* Tạo text trong game (name, score, ...)
* Làm số mạng và điểm cho nhân vật
* Chỉnh sửa và ghép code

***GIỚI THIỆU VỀ PROJECT**
* Tên game: Pixel Adventure
* Thể loại: Phiêu lưu, đi cảnh (vượt chướng ngại vật, thu thập vật phẩm để về đích)
* Tóm tắt: Game gồm có 4 nhân vật và 2 map với độ khó khác nhau để người chơi lựa chọn. Người chơi có nhiệm vụ điều khiển nhân vật của mình vượt qua các cạm bẫy (gai, đá, lưỡi cưa, ...) và kẻ địch, đồng thời thu thập hoa quả để gia tắng số điểm và đi về phía chiếc cúp để giành chiến thắng. Nếu vượt qua được cả 2 map thì sẽ phá đảo game.

***CÁC LỆNH ĐỂ CHẠY PROJECT**
* Đảm bảo máy tính đã cài đặt các thư viện SDL2, SDL2_mixer, SDL2_ttf, SDL2_image
* Bước 1(Biên dịch project): Vào thư mục Game_project mở CMD rồi nhập lệnh g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
* Bước 2(Chạy game): Nhập main.exe 
