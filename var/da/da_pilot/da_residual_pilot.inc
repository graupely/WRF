subroutine da_residual_pilot(iv, y, re, np_missing, np_bad_data, np_obs_used, np_available)

   !-----------------------------------------------------------------------
   ! Purpose: Calculate residuals for pilots
   !-----------------------------------------------------------------------

   implicit none

   type (iv_type), intent(in)    :: iv     ! Innovation vector (O-B).
   type (y_type) , intent(in)    :: y      ! y = H (xa)
   type (y_type) , intent(inout) :: re     ! Residual vector (O-A).

   integer       , intent(inout) :: np_available
   integer       , intent(inout) :: np_obs_used
   integer       , intent(inout) :: np_missing
   integer       , intent(inout) :: np_bad_data

   type (bad_data_type) :: n_obs_bad
   integer              :: n, k

   if (trace_use_dull) call da_trace_entry("da_residual_pilot")

   n_obs_bad % u % num = number_type(0, 0, 0)
   n_obs_bad % v % num = number_type(0, 0, 0)

   do n=1, iv%info(pilot)%nlocal
      do k=1, iv%info(pilot)%levels(n)
         np_available = np_available + 2
         re%pilot(n)%u(k) = da_residual(n, k, y%pilot(n)%u(k), iv%pilot(n)%u(k), n_obs_bad % u)
         re%pilot(n)%v(k) = da_residual(n, k, y%pilot(n)%v(k), iv%pilot(n)%v(k), n_obs_bad % v)
      end do
   end do

   np_missing  = np_missing  + n_obs_bad % u % num % miss + n_obs_bad % v % num % miss
   np_bad_data = np_bad_data + n_obs_bad % u % num % bad + n_obs_bad % v % num % bad 
   np_obs_used = np_obs_used + n_obs_bad % u % num % use + n_obs_bad % v % num % use

   if (trace_use_dull) call da_trace_exit("da_residual_pilot")

end subroutine da_residual_pilot


