SELECT movies.title
FROM movies
JOIN stars ON stars.movie_id = movies.id
JOIN ratings ON ratings.movie_id = movies.id
WHERE stars.person_id IN (
    SELECT people.id
    FROM people
    WHERE name = 'Chadwick Boseman'
)
ORDER BY ratings.rating DESC
LIMIT 5;
