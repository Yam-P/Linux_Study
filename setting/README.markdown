## vim plugin 받는 방법
1. vim plugin git으로부터 Vundle을 클론한다.
   링크: git clone https://github.com/VundleVim/Vundle.vim.git
2. .vimrc에 위의 github 페이지에 있는 "3. Configure: " 아래 내용들을 붙인다.
3. vim에서 :source % 와 :PluginInstall을 입력하여 .vimrc에 기입한 Plugin들을 설치한다.  
	> 참고: 아래 플러그인들은 https://vimawesome.com/ 로부터 받아서 수행.

### NERDTree  

- 목적: vim 파일을 사용 중에, 다른 파일을 열거나 directory 구조를 보고 싶을 때 사용.

- 설치 방법  

1. Search에서 The NERD tree를 검색한다.
2. .vimrc에서 Vundle을 받을 때 있었던 Plugin들이 있는 곳을 찾는다.
3. 마음에 드는 위치에  Plugin 'scrooloose/nerdtree'를 추가한다.
4. Vundle을 받았을 때와 마찬가지로 :source % 와 :PluginInstall을 입력한다.

- 사용 방법  

1. vim으로 텍스트를 연 후, :NERDTree 를 치고 엔터를 누른다.  
2. vim과 같이 j, k로 이동 가능하며, 아래 단축어를 통해 기능을 사용한다.  
	> u: 현재 working diredtory 확장
	> C: working directory를 커서의 directory로 변경
	> r: 새로고침
	> i: 새창에 해당 커서 파일 분할해서 열기
	> t: 새탭에 해당 커서 파일 열기
3. 사이드 바와 vim 파일을 오가는 명령어는 기존 vim 명령어와 같이 Ctrl+w+[h,j,k,l].
4. NERDTree를 종료하려면 NERDTree 화면으로 이동 후,  :q

### YouCompleteMe  

- 목적: 코딩의 편의성을 높이기 위한 Intellegence를 사용하기 위함.

- 기능  

1. 함수를 사용할 때 타이핑 전에 나머지 부분들을 보여준다. 
2. 일반적인 IDE와 방식은 동일하나, 확장시 tab이 아닌 Ctrl+n을 이용하여 사용한다.
3. 문법적으로 틀린 부분을 감지했을 때 >> 마크를 왼쪽에 띄우며 표시해준다.

- 설치 방법  
 
1. Search에서 youcompleteme를 검색한다.
2. NERDTree에서와 같이 Plugin 'valloric/youcompleteme'를 추가한다.
3. Vundle을 받았을 때와 마찬가지로 :source % 와 :PluginInstall을 입력한다.
4. 이 때, youcompleteme 폴더가 생성되는데, 아래로 이동한다.
	> $ cd ~/.vim/bundle/YouCompleteMe
	> $ sudo apt-get install -y python3-dev  
	
5. YouCompleteMe는 intellegence 역할을 하는 Plugin이기 때문에, 모든 컴파일러를 미리 다운 받는다.
	> $ sudo apt-get install -y build-essential cmake gcc clang gdb 
6. install.py를 수행시키면 모든 언어에 대한 intellegence가 다운되므로, 선별하여 설치하기 위해 목록을 본다.
	> $ python3 install.py --help
7. 원하는 언어를 다운 받고 싶으면 아래와 같은 명령어를 수행한다. (아래는 c, c++관련)
	> python3 install.py --clang-completer --clangd-completer  


### Tagbar  

- 목적: 만든 함수 간에 의존성을 파악하고, 함수 목록을 관리하기 위함.  

- 설치 방법  

1. Search에서 Tagbar를 검색한다.
2. NERDTree에서와 같이 Plugin 'majutsushi/tabar'를 추가한다.
3. Vundle을 받았을 때와 마찬가지로 :source % 와 :PluginInstall을 입력한다.  
	
4. ctags라는 종속적인 패키지가 필요하므로 터미널에서 추가로 설치한다.
	> $ sudo apt-get install ctags cscope
5. vim을 통해 파일을 열고, :Tagbar 를 입력한다.

###  VIM-AIRLINE

- 목적: vim의 상태를 파악하고, 열린 페이지들을 관리하기 위함.

- 설치 방법  

1. Search에서 vim-airline을 검색한다.
2. NERDTree에서와 같이 아래 두 줄의 명령어들을 추가한다.  
	> Plugin 'vim-airline/vim-airline'
	> Plugin 'vim-airline/vim-airline-themes'
3. Vundle을 받았을 때와 마찬가지로 :source % 와 :PluginInstall을 입력한다.  

- 사용 방법  

1. 빔에서 여러개의 파일을 열었을 때 사용하는 명령어인 :bn 과 :bp 를 통해 다른 탭으로 이동할 수 있다.

### vim
