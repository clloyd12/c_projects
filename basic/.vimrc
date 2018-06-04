" Execute program
nnoremap <leader>e :w<CR> :call ScreenShellSend("build/main")<CR>
" nnoremap <leader>e :w<CR> :call ScreenShellSend("build/fileops")<CR>
" nnoremap <leader>e :w<CR> :call ScreenShellSend("build/stringops")<CR>
" nnoremap <leader>e :w<CR> :call ScreenShellSend("build/functors")<CR>

" Debug program
" nnoremap <leader>g :w<CR> :call ScreenShellSend("gdb -tui build/fileops")<CR>
" nnoremap <leader>g :w<CR> :call ScreenShellSend("gdb build/fileops")<CR>
nnoremap <leader>g :w<CR> :call ScreenShellSend("gdb -tui build/main")<CR><CR>

" Set breakpoint
nnoremap <leader>b :w<CR> :call ScreenShellSend("break " . @% . ":" . line("."))<CR>

" CMake settings
let g:cmake_build_type="Debug"

" Project include paths for vim
set path+=include
set path+=src

