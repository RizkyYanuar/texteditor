## TEXT EDITOR RIHANA TEAM
Text editor ini kami buat untuk menyelesaikan tugas mata kuliah Proyek 2: Pengembangan Aplikasi Berbasis Library.

# FITUR UTAMA
- New File  
Fitur ini digunakan untuk menghasilkan file baru. Untuk menghasilkan file baru, ketik CTRL + S dan masukkan nama file berserta ekstensinya. Apabila file belum ada, hasilkan file baru. Apabila file sudah ada, overwrite file tersebut.
- Open File  
Fitur ini digunakan untuk membuka file yang sudah ada.
- Delete File  
Fitur ini digunakan untuk menghapus file yang sudah ada.
- Exit  
Fitur ini digunakan untuk keluar dari program.

# MODUL YANG DIGUNAKAN
- MODUL YANG DIBUAT OLEH HAFIEZ  
a.Modul Set Cursor untuk visualisasi cursor di CLI  
b.Modul PCX untuk merubah koordinat x cursor  
c.Modul PCY untuk merubah koordinat y cursor  
d.Modul gerak kursor untuk memindahkan kursor ke kanan,kiri,atas,bawah di backend  
e.Modul baris baru dimana dapat menambahkan baris baru  
f.Modul insert karakter dimana dapat menginputkan karakter  
g.Modul selecting dimana dapat memilih beberapa karakter / selecting  
h.Modul hitung panjang untuk menghitung jumlah karakter disebelah kiri cursor  
i.Modul paste untuk mempaste sejumlah karakter kedalam suatu baris  
  
- MODUL YANG DIBUAT OLEH NAJWAN  
1.freeAll()   
Digunakan untuk membebaskan seluruh memori linked list baris dan kolom yang telah dialokasikan menggunakan malloc()  
2.SaveFile()   
Digunakan untuk menyimpan isi linked list ke dalam file teks (.txt). Setiap node kolom ditulis menjadi karakter dalam file.  
3.BukaFile()   
Digunakan untuk membuka file dengan mode baca ("r"). Mengembalikan pointer FILE* yang akan digunakan oleh fungsi lain.  
4.OpenFileToLinkedList()   
Digunakan untuk membaca isi file karakter per karakter dan mengubahnya menjadi struktur linked list yang digunakan editor teks.  
5.TampilIsiFile()   
Digunakan untuk menampilkan seluruh isi file ke layar menggunakan printf()  
6.HapusFile()   
Digunakan untuk:  
1.Memastikan file ada dengan membuka file terlebih dahulu.  
2.Membebaskan seluruh memori linked list menggunakan freeAll().  
3.Menghapus file dari penyimpanan menggunakan remove()  

- MODUL YANG DIBUAT OLEH RIZKY  
1. printBar();   
Digunakan untuk menampilkan isi Linked List ke layar  
2. backspace();   
Prosedur utama yang digunakan untuk menghapus karakter  
3. backspaceSelecting();   
Hasil Pemodularan dari backspace yang digunakan untuk menghapus teks yang di select dalam satu baris  
4. backspaceNormal();   
Hasil Pemodularan dari backspace yang digunakan untuk menghapus teks tunggal  
5. CekClipboard();   
Digunakan untuk mengecek apakah clipboard sudah ada ketika melakukan CTRL + C atau CTRL + X. Nantinya apabila clipboard sudah ada maka clipboard tersebut akan di free agar setelahnya ketika di malloc clipboard baru, node clipboard lama sudah di-free.  
6. CopyToClipboard();   
Digunakan untuk menyalin teks yang di select menjadi sebuah linked list lengkap yang terdiri dari node baris (yang merepresentasikan node utama clipboard) dan node kolom (yang merepresentasikan setiap huruf yang disalin). Fungsi ini mengembalikan node baris yang berisi teks yang disalin.  
7. Copy();   
Hasil pemodularan dari fungsi CopyToClipboard yang digunakan untuk me-malloc node kolom (yang merepresentasikan setiap huruf) yang nantinya node pertama (bisa disebut juga sebagai huruf pertama yang di-copy) akan ditunjuk oleh node baris.  

# SHORT CUT DALAM MENGGUNAKAN TEKS EDITOR
CTRL + C : Menyalin teks yang diselect  
CTRL + X : Memotong teks yang diselect  
CTRL + P : Mencetak teks yang disalin  
CTRL + S : Menyimpan isi file  

# KESULITAN & TANTANGAN SELAMA PENGERJAAN PROYEK
- Hafiez  
Kesulitan ketika membuat modul-modul tersebut adalah passing parameternya dan logika-logika ketika kondisi tertentu seperti ditengah baris, awal baris , dan ujung baris jadi memerlukan waktu berpikir lebih untuk memikirkan kemugkinan - kemungkinan yang terjadi  
- Najwan  
Kesulitan yang saya alami adalah ketika membuat open file karena di modul open file ini saya menggunakan 2 modul yaitu bukafile untuk membuka file lalu open file to linkedlist untuk mengubah isi file menjadi linked list selain itu kesulitan saat membuat program ini juga sering kali mengalami error seperti isi file yang tidak terbaca,lalu yang kedua adalah saat membuat hapus file yang dimana hapus file ini awalnya saya membuat nya hanya langsung menghapus isi filenya tanpa melakukan free saat file itu di hapus sehingga banyak sekali memakan memori  
- Rizky  
Kesulitan yang saya hadapi adalah mencari bagaimana konsep linked list yang nantinya akan digunakan, karena selain memikirkan penggunaan memorinya juga, saya memikirkan bagaimana kemudahan penggunaan konsep linked list nantinya. Selain itu, membuat suatu algoritma itu ternyata sangat tricky, dimana salah penempatan urutan saja bisa membawa kita ke kondisi yang buruk. Debugging juga menjadi salah satu tantangan yang saya hadapi karena di bahasa pemrograman c, melakukan debugging itu tidak semudah seperti bahasa pemrograman yang lain.  

# KESAN PESAN SELAMA MELAKSANAKAN MATA KULIAH PROYEK
- Hafiez  
Saya lebih menyukai penggunaan linked list ketimbang array karena tidak memerlukan logika sebanyak jika menggunakan array, dan tentunya pada penerapan linkedlist ini saya sangat mengurangi penggunaan AI, saya sadar bahwa ketergantungan terhadap AI itu tidak baik jika ingin bekembang, bagi saya Project semester 2 ini sagat membangun diri saya untuk lebih berpikir kritis.  
- Najwan  
Kesan pesannya untuk teman kelompok saya sendiri terimakasih banyak udah meluangkan waktu untuk selalu membantu saya dalam menyusun code atau pun membantu memvisualisasikan bagaimana tracing yang benarnya,lalu kesan pesan lainnya saya senang dengan projek ini juga saya dapat belajar bahwasannya ketika membuat program kita tidak hanya harus menampilkan produk yang baik saja tetapi saya juga perlu memahmi bagaimana mekanismenya,lalu fungsi code yang saya pakai.  
- Rizky  
Selama mengerjakan proyek ini, saya mempelajari banyak hal seperti bagaimana kita menjadi seorang konseptor yang memikirkan bagaimana aplikasi akan dikembangkan. Saya harus memperhatikan skalabilitas kode dan efisiensi kode yang dibuat juga. Dalam mata kuliah ini, kemampuan dalam bekerja sama dalam tim menjadi salah satu faktor keberhasilan yang penting, bukan hanya kemampuan teknis saja yang dibutuhkan, tetapi kemampuan berkomunikasi juga menjadi kunci. Selain itu, saya juga belajar dan lebih memahami lagi workflow dalam menggunakan git bersama rekan, karena sebelumnya saya menggunakan git hanya untuk kepentingan pribadi saja. Saya mengucapkan terimakasih kepada hafiez dan najwan karena telah bekerjasama dengan baik selama pengerjaan proyek ini.  

# PENUTUP
Dengan segala kelebihan dan kekurangan RIHANAteam, kami mengucapkan terimakasih kepada rekan kami yang telah berjuang bersama menyelesaikan tugas proyek ini, meskipun kami mengalami banyak tantangan dan kesulitan, kami bekerja sama untuk menyelesaikan masalah yang timbul. Melalui mata kuliah proyek ini, kami berharap kedepannya apa yang telah kami lakukan menjadi pembelajaran penting yang dapat menjadi manfaat bagi diri kami kedepannya. Selain itu, terimakasih kepada para manajer khususnya Pak Riza yang telah membersamai kami dalam melaksanakan mata kuliah proyek ini. Kami mengerjakan proyek ini dengan sepenuh hati.


Salam, RIHANAteam.  
~Hafiez, Rizky, Najwan

# DAFTAR ANGGOTA
1. Hafiez Novrizal Putra - NIM. 251511011
2. Najwan Rachman - NIM. 251511024
3. Rizky Yanuar Irawan - NIM. 251511029