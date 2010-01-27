/* Data conversion to and from OCaml and R. */


/**  Cons operation in R.
  *
  *  @param car The head element.
  *  @param tail The tail list.
  *  @return The result of consing car and tail.
  */
CAMLprim value ocamlr_cons (value car, value tail) {
  return(Val_sexp(CONS(Sexp_val(car), Sexp_val(tail))));
}


/**  Tagging a pairlist's head
  *
  *  @note This function is specifically used when constructing
  *        a LANGSXP for evaluation with named arguments.
  *
  *  @param s The pairlist.
  *  @param t The tag, as a string.
  */
CAMLprim value ocamlr_tag (value s, value t) {
  SET_TAG(Sexp_val(s), install(String_val(t)));
  return Val_unit;
}


/**  Creating a call out of a pairlist.
  *
  *  @param s A pairlist, containing function and arguments.
  *  @return An executable version of the pairlist, with a head
  *          element sexptyped as a LANGSXP.
  */
CAMLprim value ocamlr_set_langsxp (value s) {
  SET_TYPEOF(Sexp_val(s), LANGSXP);
  return Val_unit;
}


/**  Converts an internal CHARSXP structure to an OCaml string.
  *
  *  @param charsxp A CHARSXP structure, i.e. an R internal string.
  *  @return An OCaml string.
  */
CAMLprim value ocamlr_internal_string_of_charsxp (value charsxp) {

  /* When using the R API, this issues a function call. When using
     the #define USE_RINTERNALS directive, it is more efficient. */

  /* It is yet unclear whether or not R strings are NULL
     terminated or size-delimited. I was told that R produces NULL
     terminated strings, but I haven't managed to get information
     on whether I should expect size-delimited strings originating
     from somewhere else... */

  return(caml_copy_string(CHAR(Sexp_val(charsxp))));
}


/**  Converts an OCaml string to an internal CHARSXP structure.
  *
  *  @param s An OCaml string.
  *  @return A CHARSXP structure.
  */
CAMLprim value ocamlr_charsxp_of_string (value s) {

  /* Documentation for generating R strings can be found in "Writing R
     extensions", section 5.9.7 "Handling character data". */

  return(Val_sexp(mkChar(String_val(s))));
}


/**  Converts an OCaml string to a STRSXP structure.
  *
  *  @param s An OCaml string.
  *  @return A STRSXP structure representing the string.
  */
CAMLprim value ocamlr_strsxp_of_string (value s) {
  return(Val_sexp(mkString(String_val(s))));
}
