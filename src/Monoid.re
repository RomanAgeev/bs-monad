module type T = {
    type t;

    let mappend: (t, t) => t;
    let mempty: unit => t;
};