# UDP Demo
UE4でUDP通信を扱う際のデモプロジェクトです。  
  
デモ内容の解説ページはこちらです。  
http://historia.co.jp/?page_id=4188  
  
## 構成

* Binaries
   * Stub  
UDP通信でUE4側にプロパティ変更パケットを送るためのGUIアプリケーションです。  
UDPStub.exe を実行することで利用できます。  
 
   * UE4  
GUIから受け取ったプロパティ変更をプレビューするUE4アプリケーションです。  
UDPCommunication.exe を実行することで利用できます。  
 
* UDPCommunication  
UE4アプリケーションのプロジェクトです。  
4.11.2 で動作確認してあります。  
Generate Visual Studio project files からソリューションを作成してビルドして下さい。  
 
* UdpStub
GUIアプリケーションのプロジェクトです。  
UdpStub.sln を開いてビルドして下さい。  
 
