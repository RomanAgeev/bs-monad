type result('good, 'bad) = 
    | Ok('good)
    | Error('bad);

module type T = {
    include Monad.T;

    type e;

    let make: result('a, e) => t('a);
    let extract: t('a) => result('a, e);
};

module Make = (E: { type t; }): (T with type e := E.t) => {
    type t('a) = result('a, E.t);

    let bind = (x, f) => switch x {
        | Ok(good) => f(good)
        | Error(_) as e => e
    };
    let return = x => Ok(x);

    let make = x => x;
    let extract = x => x;
};