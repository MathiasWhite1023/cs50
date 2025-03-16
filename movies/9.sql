SELECT people.name
FROM stars
JOIN people ON people.id = stars.person_id
WHERE stars.movie_id
IN (SELECT id FROM movies WHERE year = 2004)
ORDER BY people.birth ASC;
