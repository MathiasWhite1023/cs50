SELECT movies.title FROM movies JOIN stars AS s1 ON s1.movie_id = movies.id
JOIN stars AS s2 ON s2.movie_id = movies.id
WHERE s1.person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper')
AND s2.person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence');
