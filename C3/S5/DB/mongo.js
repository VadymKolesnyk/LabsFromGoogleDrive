db.groups.insertMany([
    {
        "name" : "Год Змеи",
        "year" : 2001,
        "albums" : 
        [
            {
                "title" : "Линия жизни",
                "year" : 2002,
                "songs" : 
                [
                    "Я знаю...", 
                    "Я научу тебя", 
                    "Гудвин", 
                    "На...", 
                    "5 ml", 
                    "Не бойся", 
                    "Линия жизни", 
                    "33", 
                    "С новым гадом", 
                    "Первая кровь", 
                    "Две части"
                ]
            },
            {
                "title" : "Змеелов",
                "year" : 2011,
                "songs": 
                [
                    "Пролог",
                    "Выбираю",
                    "Зови",
                    "Прости",
                    "Змеелов",
                    "Икар",
                    "Танцуй",
                    "Ветер",
                    "Ангел",
                    "Проститутка Весна",
                    "Сколько",
                    "Штучки",
                    "Если",
                    "Айда",
                    "Шоу",
                    "Радуйся",
                    "Эпилог"
                ]
            }
        ]    
    },
    {
        "name" : "Гражданская Оборона",
        "year" : 1984,
        "solist" : 
        {
           "name" : "Егор",
           "surname" : "Летов" 
        }
    },
    {
        "name" : "Noize MC",
        "year" : 2008,
        "solist" : 
        {
            "name" : "Иван",
            "surname" : "Алексеев",
            "birthdy" : new Date("1985-03-09")
        },
        "albums" : 
        [
            {
                "title" : "The Greatest Hits Vol. 1 ",
                "year" : 2008,
                "songs" : 
                [
                    "Песня для радио",
                    "За закрытой дверью",
                    "Из окна",
                    "Москва — не резиновая",
                    "Кантемировская",
                    "ЖИЗНЬ без наркотиков",
                    "На районе (3 недели нету плана)",
                    "На работе (платят бабло)",
                    "Кури бамбук!",
                    "Палево!",
                    "Блатняк",
                    "5П", 
                    "Девочка-скинхед",
                    "Наше движение",
                    "АренбиШ",
                    "Поднимите руки ",
                    "Моё море",
                    "Выдыхай",
                    "ЗП", 
                    "Мы всего добились сами", 
                ]
            },
            {
                "title" : "Царь горы",
                "year" : 2016,
                "songs" : 
                [
                    "Make Some Noize",
                    "Стэнли запишет хит",
                    "Царь горы",
                    "Эмпайр Стэйт",
                    "Гвозди", 
                    "Грабли",
                    "Чайлдфри", 
                    "Face À La Mer", 
                    "Всё ОК", 
                    "Джеймесон",
                    "Питерские крыши",
                    "Кислотный дождь",
                    "Любимый цвет",
                    "!L!VE!",
                ]
            },
            {
                "title" : "Неразбериха",
                "year" : 2013,
                "songs" :
                [
                    "+-0",
                    "Нету паспорта", 
                    "Настоящего",
                    "Нам не ПОНЯТЬ", 
                    "Жирный чёрный пробел",
                    "Ненавижу",
                    "Тёмную сторону СИЛЫ", 
                    "Влиятельные покровители",
                    "Не надо было",
                    "Чебуречная",
                    "Капитан Америка",
                    "Нероссия", 
                    "Неразбериха",
                    "Безмозглая музыка",
                    "Гой еси",
                    "Game Over",
                    "Жвачка"
                ]
            }
        ]
    },
    {
        "name" : "Wovenhand",
        "year" : 2001
    },
    {
        "name" : "Twenty One Pilots",
        "year" : 2009,
        "solist" : 
        {
            "name" : "Tyler",
            "surname" : "Joseph"
        }
    }
])

//-------------------------------//
db.countries.insertMany([
    {
        "_id" : "us",
        "name" : "USA",
        "nameInNationalLanguage" : "United States of America",
        "capital" : "Washington",
        "capitalInNationalLanguage" : "Washington",
        "lenguage" : "english"
    },
    {
        "_id" : "ru",
        "name" : "Russia",
        "nameInNationalLanguage" : "Россия",
        "capital" : "Moscow",
        "capitalInNationalLanguage" : "Москва",
        "lenguage" : "rusian"        
    },
    {
        "_id" : "ua",
        "name" : "Ukraine",
        "nameInNationalLanguage" : "Україна",
        "capital" : "Kyiv",
        "capitalInNationalLanguage" : "Київ",
        "lenguage" : "ukrainian" 
    }
])
//----------------------//
db.groups.bulkWrite([
    {
        updateOne : {
            filter : {name : "Год Змеи"},
            update : {$set : {"countryId":"ru"}}
        }
    },
    {
        updateOne : {
            filter : {name : "Гражданская Оборона"},
            update : {$set : {"countryId":"ru"}}
        }
    },
    {
        updateOne : {
            filter : {name : "Noize MC"},
            update : {$set : {"countryId":"ru"}}
        }
    },
    {
        updateOne : {
            filter : {name : "Wovenhand"},
            update : {$set : {"countryId":"us"}}
        }
    },
    {
        updateOne : {
            filter : {name : "Twenty One Pilots"},
            update : {$set : {"countryId":"us"}}
        }
    }
])

//---------------------------//
> db.groups.find(
    {
    countryId : 
    {
        $in : db.countries.find({lenguage: "english"}).map(u => u._id)}
    },
    {_id:false}
).pretty()

//------------------------//
db.groups.mapReduce(
    function() { emit(this.year , 1) },
    function(key,values){return Array.sum(values) },
    {out: {inline: 1}}
)
//------------------------//
db.groups.mapReduce(     
    function() { emit(this.countryId , this.name) },     
    function(key,values){return values },     
    {out: {inline: 1}} 
)