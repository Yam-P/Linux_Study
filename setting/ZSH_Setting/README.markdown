# zsh setting

## zsh쉘 설치 및 oh-my-zsh

1. zsh 설치하기
	```
	$ sudo apt install zsh
	```

2. zsh 위치 파악 후 쉘 변경
	```
	$ which zsh  
	$ chsh -s /usr/bin/zsh (which zsh 결과가 /usr/bin/zsh라면)
	```

3. oh-my-zsh를 clone하기 위한 패키지 설치
	```
	$ sudo apt install git curl
	```

3. oh-my-zsh 설치
	```
	$ sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
	```


## oh-my-zsh 테마 변경 및 plugin
### 테마 변경
1. .zshrc에서 ZSH_THEME 부분을 "robbyrussell"에서 "agnoster"로 변경
	```
	$ vim ~/.zshrc
	```
2. 터미널에서 source .zshrc 명령어를 통해
	```
	$ source ~/.zshrc
	```
3. font 문제가 생겨서 모양이 깨져서 나온다면, 폰트 설치
	```
	$ sudo apt install fonts-powerline
	```

### 프롬프트 멀티라인으로 설정
1. multi line으로 검색을 원한다면, agnoster 테마를 열기.
	```
	$ vim ~/.oh-my-zsh/themes/agnoster.zsh-theme  
	```
2. '## Main prompt(prompt 설정을 사용하는 부분)' 상단에 아래 내용을 추가.
	```
	prompt_newline() {
	 if [[ -n $CURRENT_BG ]]; then
	  echo -n "%{%k%F{$CURRENT_BG}%}$SEGMENT_SEPARATOR
	%{%k%F{blue}%}$SEGMENT_SEPARATOR"
	 else
	  echo -n "%{%k%}"
	 fi
	  echo -n "%{%f%}"
	  CURRENT_BG=''
	```

3. '## Main prompt'에 이를 반영하여 아래와 같이 되어야 함.
	```
	build_prompt() {  
	  RETVAL=$?  
	  prompt_status  
	  prompt_virtualenv  
	  prompt_context  
	  prompt_dir  
	  prompt_git  
	  prompt_hg  
	  prompt_newline  
	  prompt_end  
	}  
	```

### autosuggestions 플러그인 설치
1. plugin 폴더로 이동
	```
	$ cd ~/.oh-my-zsh/plugins
	```
2. 자동완성 관련 git을 클론하여 폴더 생성
	```
	$ git clone https://github.com/zsh-users/zsh-autosuggestions.git
	```
3. .zshrc이 실행될 때 zsh-autosuggestions.zsh를 실행하도록 세팅
	```
	$ echo "source ${(q-)PWD}/zsh-autosuggestions/zsh-autosuggestions.zsh" >> ${ZDOTDIR:-$HOME}/.zshrc
	```
4. 위 명령어가 잘 수행됐는지 확인하기 위해 .zshrc 확인(가장 밑줄)
	```
	$ vim ~/.zshrc  
	```
5. .zshrc 적용
	```
	$ source ~/.zshrc
	```

### hilighting 플러그인 설치
1. plugin 폴더로 이동
	```
	$ cd ~/.oh-my-zsh/plugins
	```
2. 강조구문 관련 git을 클론하여 폴더 생성
	```
	$ git clone https://github.com/zsh-users/zsh-syntax-highlighting.git
	```
3. autosuggestions와 같이 .zshrc에 추가
	```
	$ echo "source ${(q-)PWD}/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> ${ZDOTDIR:-$HOME}/.zshrc
	```
4. 위 명령어가 잘 수행됐는지 확인하기 위해 .zshrc 확인(가장 밑줄)
	```
	$ vim ~/.zshrc  
	```
5. .zshrc 적용
	```
	$ source ~/.zshrc
	```
