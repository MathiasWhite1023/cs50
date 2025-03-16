SELECT people.name
FROM directors
JOIN people ON people.id = directors.person_id
WHERE directors.movie_id IN (
    SELECT movies.id
    FROM movies
    JOIN ratings
    ON ratings.movie_id = movies.id
    WHERE ratings.rating >= 9.0);
