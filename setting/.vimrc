set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'tpope/vim-fugitive'
Plugin 'rstacruz/sparkup', {'rtp': 'vim/'}

Plugin 'scrooloose/nerdtree'
Plugin 'Valloric/YouCompleteMe'
Plugin 'majutsushi/tagbar'
Plugin 'nathanaelkane/vim-indent-guides'
let g:indent_guides_enable_on_vim_startup = 1
Plugin 'airblade/vim-gitgutter'
let g:gitgutter_max_signs = -1

Plugin 'vim-airline/vim-airline'
Plugin 'vim-airline/vim-airline-themes'
let g:airline#extensions#tabline#enabled = 1
let g:airline#extensions#tabline#left_sep = ' '
let g:airline#extensions#tabline#left_alt_sep = '|'
let g:airline#extensions#tabline#formatter = 'unique_tail'

call vundle#end()
filetype plugin indent on

Plugin 'blueyed/vim-diminactive'
let g:diminactive_enable_focus = 1

Plugin 'pandark/42header.vim'
nmap <f1> :FortyTwoHeader<CR>
"Plugin 'terryma/vim-multiple-cursors'

" my Key Binding ===============================
nmap <F9> :NERDTree<CR>
nmap <F8> :Tagbar<CR>
"nmap <C-]> :bn<CR>
"nmap <C-[> :bp<CR>

nmap <C-H> <C-W>h
nmap <C-J> <C-W>j
nmap <C-K> <C-W>k
nmap <C-L> <C-W>l
nmap <A-H> <C-W><
nmap <A-J> <C-W>+
nmap <A-K> <C-W>-
nmap <A-L> <C-W>>

" my Setting ===================================
set hlsearch
set nu
set autoindent
set scrolloff=2
set wildmode=longest,list
set ts=4
set sts=4
set sw=1
set autowrite
set autoread
set cindent
set bs=eol,start,indent
set history=256
set laststatus=2
set paste
set shiftwidth=4 
set showmatch
set smartcase
set smarttab
set smartindent
set softtabstop=4
set tabstop=4
set ruler
set incsearch
set statusline=\ %<%l:%v\ [%P]%=%a\ %h%m%r\ %F\

au BufReadPost *
			\ if line("'\"") > 0 && line("'\"") <= line("$") |
			\ exe "norm g`\"" |
			\ endif

if $LANG[0]=='k' && $LANG[1]=='o'
	set fileencoding=korea
endif

if has("syntax")
	 syntax on
 endif

 colorscheme jellybeans
