# Configurations
client_width      = 8
client_height     = 9
# 8072 is w8h9
#max_posix_thread  = 128
max_posix_thread  = client_width * client_height * 5
max_pthread_mutex = 409600
max_pthread_cond  = 204800

# Enable dynamic semaphore control block allocation
dynamic_semcb_allocation = True
#max_pthread_mutex = 128
#max_pthread_cond = 128

core_number = client_width * client_height

#
# Application settings
# app_settings:     'origin' | 'best'
# kernel_spin_lock: 'tas' | 'tatas' | 'backoff' | 'k42'
# math_library:     'newlib' | 'glibc' | 'openlibm'
# memory_allocator: 'newlib' | 'tlsf' | 'hoard'
# opt_page_table:   None | 'page' | 'section'
# opt_my_p_runtsk:  None | 'fast' | 'spr'
# load_balancer:    None | 'ishida'
#
#app_settings = 'origin'
#load_balancer = 'ishida'
#app_settings = 'benchmark-malloc'
app_settings = 'fmp'
#app_settings = 'fmp-k42'

if app_settings == 'origin':
    kernel_spin_lock = 'tatas'
    memory_allocator = 'newlib'
    math_library     = 'newlib'
    opt_page_table   = None 
    opt_my_p_runtsk  = None
    load_balancer    = None

if app_settings == 'benchmark-malloc':
    kernel_spin_lock = 'backoff'
    memory_allocator = 'newlib'
    math_library     = 'newlib'
    opt_page_table   = None
    opt_my_p_runtsk  = None
    load_balancer    = None

if app_settings == 'fmp':
    kernel_spin_lock = 'backoff'
    memory_allocator = 'hoard'
    math_library     = 'glibc'
    opt_page_table   = 'section'
    opt_my_p_runtsk  = 'spr'
    load_balancer    = None

if app_settings == 'fmp-k42':
    kernel_spin_lock = 'k42'
    memory_allocator = 'hoard'
    math_library     = 'glibc'
    opt_page_table   = 'section'
    opt_my_p_runtsk  = 'spr'
    load_balancer    = None

