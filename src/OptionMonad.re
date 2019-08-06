module type T = {
    include Monad.T;

    let make: option('a) => t('a);
    let extract: t('a) => option('a);
};

module Make: T = {
    type t('a) = option('a);

    let bind = (x, f) => switch x {
        | Some(v) => f(v)
        | None => None
    };
    let return = x => Some(x);

    let make = x => x;
    let extract = x => x;
};

module Ex = Monad.Ex(Make);
