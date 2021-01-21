#allow all classes access to Pet Affinity
UPDATE `aa_ability` SET `classes` = '65535' WHERE (`id` = '250');

#allow all classes access to Pet Discipline
UPDATE `aa_ability` SET `classes` = '65535' WHERE (`id` = '125');
UPDATE `aa_ability` SET `classes` = '65535' WHERE (`id` = '3202');
