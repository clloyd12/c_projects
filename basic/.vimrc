
" Execute program
nnoremap <leader>e :w<CR> :call ScreenShellSend("build/main")<CR>

" Debug program
 nnoremap <leader>g :w<CR> :call ScreenShellSend("gdb -tui build/main")<CR>

" Set breakpoint
nnoremap <leader>b :w<CR> :call ScreenShellSend("break " . @% . ":" . " line("."))<CR>

" CMake settings
let g:cmake_build_type="Debug"

" Project include paths for vim
set path+=include
set path+=src

