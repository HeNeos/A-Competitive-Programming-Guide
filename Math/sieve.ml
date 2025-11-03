module type SIEVE = sig
  val build_sieve : int -> bool list
  val build_lpf : int -> int list
  val build_phi : int -> int list
  val extract_primes : (int -> 'a -> bool) -> 'a list -> int list
end

module Sieve = struct
  let build_sieve (n : int) : bool list =
    let is_prime = Array.make (n + 1) true in
    is_prime.(0) <- false;
    is_prime.(1) <- false;
    Array.iteri
      (fun idx _ ->
        if is_prime.(idx) then
          let rec aux k =
            if k <= n then (
              is_prime.(k) <- false;
              aux (k + idx))
          in
          aux (idx * idx))
      is_prime;

    Array.to_list is_prime

  let build_lpf (n : int) : int list =
    let least_prime_factor = Array.make (n + 1) 0 in
    Array.iteri
      (fun idx value ->
        if idx >= 2 && value == 0 then (
          least_prime_factor.(idx) <- idx;
          let rec aux k =
            if k <= n then (
              if least_prime_factor.(k) == 0 then least_prime_factor.(k) <- idx;
              aux (k + idx))
          in
          aux (idx * idx)))
      least_prime_factor;

    Array.to_list least_prime_factor

  let build_phi (n : int) : int list =
    let phi = Array.make (n + 1) 0 in
    phi.(1) <- 1;
    Array.iteri
      (fun idx value ->
        if idx >= 2 && value == 0 then (
          phi.(idx) <- idx - 1;
          let rec aux k =
            if k <= n then (
              if phi.(k) == 0 then phi.(k) <- k;
              phi.(k) <- phi.(k) / idx * (idx - 1);
              aux (k + idx))
          in
          aux (2 * idx)))
      phi;

    Array.to_list phi

  let extract_primes (is_prime_pred : int -> 'a -> bool) (data : 'a list) :
      int list =
    let rec filter_primes (idx : int) (acc : int list) = function
      | [] -> List.rev acc
      | x :: xs ->
          if is_prime_pred idx x then filter_primes (idx + 1) (idx :: acc) xs
          else filter_primes (idx + 1) acc xs
    in
    filter_primes 0 [] data
end
