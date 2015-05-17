set nocompatible
set backspace=indent,eol,start
set history=50
set showcmd

syntax enable
syntax on

colorscheme evening

set guifont=Courier\ 14
set guifontwide=永中宋体\ 14

set enc=utf-8
set nu!

filetype plugin indent on

set cindent shiftwidth=4
set autoindent
set tabstop=4
set langmenu=zh_CN.UTF-8
set fileencodings=utf-8,gb18030,utf-16,big5,gb2312,GBK
set nobackup

let g:vimrplugin_screenplugin = 1
let g:vimrplugin_underscore = 1
let g:vimrplugin_nosingler = 1
let g:vimrplugin_noscreenrc = 1

map <F3> a()<Esc>i
map <F4> a""<Esc>i
